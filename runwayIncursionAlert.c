#ifndef RUNWAY_SAFETY_CORE_H
#define RUNWAY_SAFETY_CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ============================================================================
// CONSTANTS AND DEFINITIONS
// ============================================================================

#define MAX_RUNWAYS 10
#define MAX_RUNWAY_ID_LENGTH 8
#define MAX_AIRPORT_CODE_LENGTH 5
#define EARTH_RADIUS_KM 6371.0
#define METERS_PER_KM 1000.0
#define CRITICAL_DISTANCE_METERS 50.0
#define WARNING_DISTANCE_METERS 100.0
#define CAUTION_DISTANCE_METERS 200.0

// Alert levels
typedef enum {
    ALERT_NONE = 0,
    ALERT_CAUTION = 1,  // 200m - prepare for runway
    ALERT_WARNING = 2,  // 100m - runway ahead
    ALERT_CRITICAL = 3  // 50m - STOP immediately
} AlertLevel;

// ============================================================================
// DATA STRUCTURES
// ============================================================================

typedef struct {
    double latitude;
    double longitude;
    double timestamp;  // Unix timestamp
    double speed_mps;  // meters per second
    double heading;    // degrees (0-360)
} AircraftPosition;

typedef struct {
    char runway_id[MAX_RUNWAY_ID_LENGTH];
    double start_lat;
    double start_lon;
    double end_lat;
    double end_lon;
    double heading;     // runway heading in degrees
    double width_meters;
    bool is_active;
    bool has_clearance;
    time_t clearance_timestamp;
} Runway;

typedef struct {
    char airport_code[MAX_AIRPORT_CODE_LENGTH];
    Runway runways[MAX_RUNWAYS];
    int runway_count;
    double airport_lat;
    double airport_lon;
} Airport;

typedef struct {
    AlertLevel level;
    char runway_id[MAX_RUNWAY_ID_LENGTH];
    double distance_meters;
    char message[256];
    time_t timestamp;
    bool clearance_required;
} SafetyAlert;

// ============================================================================
// CORE MATHEMATICAL FUNCTIONS
// ============================================================================

// Convert degrees to radians
double deg_to_rad(double degrees) {
    return degrees * M_PI / 180.0;
}

// Convert radians to degrees
double rad_to_deg(double radians) {
    return radians * 180.0 / M_PI;
}

// Calculate great circle distance between two points (Haversine formula)
double calculate_distance_meters(double lat1, double lon1, double lat2, double lon2) {
    double dlat = deg_to_rad(lat2 - lat1);
    double dlon = deg_to_rad(lon2 - lon1);
    
    double a = sin(dlat/2) * sin(dlat/2) + 
               cos(deg_to_rad(lat1)) * cos(deg_to_rad(lat2)) * 
               sin(dlon/2) * sin(dlon/2);
    
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double distance_km = EARTH_RADIUS_KM * c;
    
    return distance_km * METERS_PER_KM;
}

// Calculate bearing from point 1 to point 2
double calculate_bearing(double lat1, double lon1, double lat2, double lon2) {
    double dlon = deg_to_rad(lon2 - lon1);
    double lat1_rad = deg_to_rad(lat1);
    double lat2_rad = deg_to_rad(lat2);
    
    double y = sin(dlon) * cos(lat2_rad);
    double x = cos(lat1_rad) * sin(lat2_rad) - sin(lat1_rad) * cos(lat2_rad) * cos(dlon);
    
    double bearing_rad = atan2(y, x);
    double bearing_deg = rad_to_deg(bearing_rad);
    
    // Normalize to 0-360
    return fmod((bearing_deg + 360.0), 360.0);
}

// Calculate perpendicular distance from point to line (runway)
double distance_point_to_line(double px, double py, double x1, double y1, double x2, double y2) {
    double A = px - x1;
    double B = py - y1;
    double C = x2 - x1;
    double D = y2 - y1;
    
    double dot = A * C + B * D;
    double len_sq = C * C + D * D;
    
    if (len_sq < 1e-6) {
        // Line segment is essentially a point
        return sqrt(A * A + B * B);
    }
    
    double param = dot / len_sq;
    
    double xx, yy;
    if (param < 0) {
        xx = x1;
        yy = y1;
    } else if (param > 1) {
        xx = x2;
        yy = y2;
    } else {
        xx = x1 + param * C;
        yy = y1 + param * D;
    }
    
    double dx = px - xx;
    double dy = py - yy;
    return sqrt(dx * dx + dy * dy);
}

// ============================================================================
// RUNWAY SAFETY LOGIC
// ============================================================================

// Check if aircraft is approaching runway threshold
bool is_approaching_runway(AircraftPosition* aircraft, Runway* runway) {
    if (!runway->is_active) return false;
    
    // Calculate distance to both runway ends
    double dist_to_start = calculate_distance_meters(
        aircraft->latitude, aircraft->longitude,
        runway->start_lat, runway->start_lon
    );
    
    double dist_to_end = calculate_distance_meters(
        aircraft->latitude, aircraft->longitude,
        runway->end_lat, runway->end_lon
    );
    
    // Check if approaching either end
    double min_distance = (dist_to_start < dist_to_end) ? dist_to_start : dist_to_end;
    
    if (min_distance > CAUTION_DISTANCE_METERS) return false;
    
    // Check if aircraft heading is towards the runway
    double bearing_to_runway = (dist_to_start < dist_to_end) ?
        calculate_bearing(aircraft->latitude, aircraft->longitude, runway->start_lat, runway->start_lon) :
        calculate_bearing(aircraft->latitude, aircraft->longitude, runway->end_lat, runway->end_lon);
    
    double heading_diff = fabs(aircraft->heading - bearing_to_runway);
    if (heading_diff > 180) heading_diff = 360 - heading_diff;
    
    // Consider "approaching" if within 45 degrees of runway direction
    return heading_diff < 45.0;
}

// Determine alert level based on distance and clearance status
AlertLevel determine_alert_level(double distance, bool has_clearance, bool is_moving) {
    if (has_clearance) return ALERT_NONE;
    
    if (distance <= CRITICAL_DISTANCE_METERS && is_moving) {
        return ALERT_CRITICAL;
    } else if (distance <= WARNING_DISTANCE_METERS) {
        return ALERT_WARNING;
    } else if (distance <= CAUTION_DISTANCE_METERS) {
        return ALERT_CAUTION;
    }
    
    return ALERT_NONE;
}

// Main runway proximity check function
SafetyAlert check_runway_proximity(AircraftPosition* aircraft, Airport* airport) {
    SafetyAlert alert = {ALERT_NONE, "", 0.0, "", 0, false};
    time(&alert.timestamp);
    
    double min_distance = 99999.0;
    Runway* closest_runway = NULL;
    
    // Check each runway at the airport
    for (int i = 0; i < airport->runway_count; i++) {
        Runway* runway = &airport->runways[i];
        
        if (!runway->is_active) continue;
        
        // Calculate minimum distance to runway centerline
        double distance = distance_point_to_line(
            aircraft->latitude, aircraft->longitude,
            runway->start_lat, runway->start_lon,
            runway->end_lat, runway->end_lon
        ) * METERS_PER_KM;  // Convert to meters (approximate)
        
        // More accurate distance calculation for very close proximity
        if (distance < CAUTION_DISTANCE_METERS) {
            double dist_to_start = calculate_distance_meters(
                aircraft->latitude, aircraft->longitude,
                runway->start_lat, runway->start_lon
            );
            
            double dist_to_end = calculate_distance_meters(
                aircraft->latitude, aircraft->longitude,
                runway->end_lat, runway->end_lon
            );
            
            distance = (dist_to_start < dist_to_end) ? dist_to_start : dist_to_end;
        }
        
        if (distance < min_distance && is_approaching_runway(aircraft, runway)) {
            min_distance = distance;
            closest_runway = runway;
        }
    }
    
    if (closest_runway == NULL) return alert;
    
    // Determine if aircraft is moving (speed > 1 m/s = ~2 knots)
    bool is_moving = aircraft->speed_mps > 1.0;
    
    // Check clearance timestamp (clearances expire after 2 minutes)
    bool clearance_valid = false;
    if (closest_runway->has_clearance) {
        time_t current_time;
        time(&current_time);
        clearance_valid = (current_time - closest_runway->clearance_timestamp) < 120;
    }
    
    alert.level = determine_alert_level(min_distance, clearance_valid, is_moving);
    alert.distance_meters = min_distance;
    strcpy(alert.runway_id, closest_runway->runway_id);
    alert.clearance_required = !clearance_valid;
    
    // Generate appropriate message
    switch (alert.level) {
        case ALERT_CRITICAL:
            snprintf(alert.message, sizeof(alert.message),
                "STOP! RUNWAY %s AHEAD - %.0fm - NO CLEARANCE!",
                alert.runway_id, alert.distance_meters);
            break;
        case ALERT_WARNING:
            snprintf(alert.message, sizeof(alert.message),
                "WARNING: Runway %s ahead - %.0fm - Verify clearance",
                alert.runway_id, alert.distance_meters);
            break;
        case ALERT_CAUTION:
            snprintf(alert.message, sizeof(alert.message),
                "CAUTION: Approaching runway %s - %.0fm",
                alert.runway_id, alert.distance_meters);
            break;
        default:
            strcpy(alert.message, "");
            break;
    }
    
    return alert;
}

// ============================================================================
// RUNWAY CLEARANCE MANAGEMENT
// ============================================================================

// Grant runway crossing clearance
void grant_runway_clearance(Airport* airport, const char* runway_id) {
    for (int i = 0; i < airport->runway_count; i++) {
        if (strcmp(airport->runways[i].runway_id, runway_id) == 0) {
            airport->runways[i].has_clearance = true;
            time(&airport->runways[i].clearance_timestamp);
            printf("Clearance granted for runway %s\n", runway_id);
            return;
        }
    }
    printf("Runway %s not found\n", runway_id);
}

// Revoke runway clearance
void revoke_runway_clearance(Airport* airport, const char* runway_id) {
    for (int i = 0; i < airport->runway_count; i++) {
        if (strcmp(airport->runways[i].runway_id, runway_id) == 0) {
            airport->runways[i].has_clearance = false;
            printf("Clearance revoked for runway %s\n", runway_id);
            return;
        }
    }
}

// ============================================================================
// INITIALIZATION FUNCTIONS
// ============================================================================

// Initialize Ottawa Airport (CYOW) with runway data
Airport initialize_ottawa_airport() {
    Airport airport;
    strcpy(airport.airport_code, "CYOW");
    airport.airport_lat = 45.3225;
    airport.airport_lon = -75.6692;
    airport.runway_count = 5;
    
    // Runway 07-25 (Main runway)
    strcpy(airport.runways[0].runway_id, "07");
    airport.runways[0].start_lat = 45.3180;
    airport.runways[0].start_lon = -75.6890;
    airport.runways[0].end_lat = 45.3270;
    airport.runways[0].end_lon = -75.6494;
    airport.runways[0].heading = 70.0;
    airport.runways[0].width_meters = 60.0;
    airport.runways[0].is_active = true;
    airport.runways[0].has_clearance = false;
    
    // Runway 25 (opposite direction)
    strcpy(airport.runways[1].runway_id, "25");
    airport.runways[1].start_lat = 45.3270;
    airport.runways[1].start_lon = -75.6494;
    airport.runways[1].end_lat = 45.3180;
    airport.runways[1].end_lon = -75.6890;
    airport.runways[1].heading = 250.0;
    airport.runways[1].width_meters = 60.0;
    airport.runways[1].is_active = true;
    airport.runways[1].has_clearance = false;
    
    // Runway 14-32
    strcpy(airport.runways[2].runway_id, "14");
    airport.runways[2].start_lat = 45.3150;
    airport.runways[2].start_lon = -75.6750;
    airport.runways[2].end_lat = 45.3300;
    airport.runways[2].end_lon = -75.6634;
    airport.runways[2].heading = 140.0;
    airport.runways[2].width_meters = 45.0;
    airport.runways[2].is_active = true;
    airport.runways[2].has_clearance = false;
    
    // Add more runways as needed...
    
    return airport;
}

// ============================================================================
// TESTING AND DEMONSTRATION
// ============================================================================

// Test function to demonstrate the system
void run_safety_test() {
    printf("=== Runway Incursion Prevention System Test ===\n\n");
    
    Airport ottawa = initialize_ottawa_airport();
    
    // Simulate aircraft position approaching runway
    AircraftPosition aircraft;
    aircraft.latitude = 45.3200;   // Near runway 07-25
    aircraft.longitude = -75.6700;
    aircraft.speed_mps = 10.0;     // ~20 knots taxi speed
    aircraft.heading = 70.0;       // Heading toward runway
    time_t current_time;
    time(&current_time);
    aircraft.timestamp = (double)current_time;
    
    printf("Aircraft position: %.6f, %.6f\n", aircraft.latitude, aircraft.longitude);
    printf("Aircraft heading: %.1f degrees, speed: %.1f m/s\n\n", aircraft.heading, aircraft.speed_mps);
    
    // Test 1: No clearance scenario
    printf("Test 1: Approaching runway without clearance\n");
    SafetyAlert alert = check_runway_proximity(&aircraft, &ottawa);
    printf("Alert Level: %d\n", alert.level);
    printf("Message: %s\n", alert.message);
    printf("Distance: %.1f meters\n\n", alert.distance_meters);
    
    // Test 2: With clearance
    printf("Test 2: Grant clearance and test again\n");
    grant_runway_clearance(&ottawa, "07");
    alert = check_runway_proximity(&aircraft, &ottawa);
    printf("Alert Level: %d\n", alert.level);
    printf("Message: %s\n\n", alert.message);
    
    // Test 3: Critical proximity
    printf("Test 3: Critical proximity without clearance\n");
    revoke_runway_clearance(&ottawa, "07");
    aircraft.latitude = 45.3179;   // Very close to runway threshold
    aircraft.longitude = -75.6885;
    alert = check_runway_proximity(&aircraft, &ottawa);
    printf("Alert Level: %d\n", alert.level);
    printf("Message: %s\n", alert.message);
    printf("Distance: %.1f meters\n\n", alert.distance_meters);
}

// Main function for testing
int main() {
    printf("Runway Incursion Prevention System - C Core\n");
    printf("==========================================\n\n");
    
    run_safety_test();
    
    return 0;
}

#endif // RUNWAY_SAFETY_CORE_H