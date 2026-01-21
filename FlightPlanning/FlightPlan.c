#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define  MAX_AIRPORTS 10000
#define PI 3.14159265358979323846
#define EARTH_RADIUS 6371 /* KM */
#define KM_TO_NM 0.54

struct Airport
{
    char code[4];  
    double latitude;
    double longitude;
};

double toRadians(double degree) {
    return degree * (PI / 180.0);
}
int loadAirports(const char *filename, struct Airport airports[], int max) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Cannot open airports.dat");
        return 0;
    }
    char line[1024];
    int count = 0;
    while (fgets(line, sizeof(line), file) && count < max) {
        char code[8];
        double lat, lon;
        // The format is: ...,"IATA",...lat,lon,...
        // We'll use sscanf to extract the 5th, 7th, and 8th fields
        // But since fields may have commas in quotes, let's use strtok for simplicity

        // Tokenize line
        char *tokens[10];
        int i = 0;
        char *token = strtok(line, ",");
        while (token && i < 10) {
            tokens[i++] = token;
            token = strtok(NULL, ",");
        }
        if (i >= 8) {
            // Remove quotes from IATA code
            char *iata = tokens[4];
            if (iata[0] == '"') iata++;
            iata[3] = '\0'; // Ensure only 3 chars
            // Only add if code is 3 letters and not empty
            if (strlen(iata) == 3 && iata[0] != '\\' && iata[0] != '\0') {
                strncpy(airports[count].code, iata, 4);
                airports[count].latitude = atof(tokens[6]);
                airports[count].longitude = atof(tokens[7]);
                count++;
            }
        }
    }
    fclose(file);
    return count;
}
struct Airport *findAirport(struct Airport airports[], int n, const char *code) {
    for (int i = 0; i < n; i++) {
        if (strcmp(airports[i].code, code) == 0)
            return &airports[i];
    }
    return NULL;
}


double calculateDistance(struct Airport departure, struct Airport arrival) {
    double lat1 = toRadians(departure.latitude);
    double lat2 = toRadians(arrival.latitude);
    double lon1 = toRadians(departure.longitude);
    double lon2 = toRadians(arrival.longitude);

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = sin(dlat/2) * sin(dlat/2) + cos(lat1) * cos(lat2) * sin(dlon/2) * sin(dlon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));

    double distance = EARTH_RADIUS * c;
    return distance;
}

void inputAirport(struct Airport *airport, const char *type) {
    printf("Enter %s airport code (3 letters): ", type);
    scanf("%3s", airport->code);
    printf("Enter %s airport latitude: ", type);
    scanf("%lf", &airport->latitude);
    printf("Enter %s airport longitude: ", type);
    scanf("%lf", &airport->longitude);
}


int main() {
     struct Airport airports[MAX_AIRPORTS];
     struct Airport departure, arrival ; 
     double distance;
     int numAirports = loadAirports("airports.dat", airports, MAX_AIRPORTS);
     struct Airport *ap = findAirport(airports, numAirports, airports->code);
    if (ap) {
        printf("Airport %s: Latitude %.6f, Longitude %.6f\n", ap->code, ap->latitude, ap->longitude);
    } else {
        printf("Airport code not found!\n");
    }

     inputAirport(&departure, "departure");
     inputAirport(&arrival, "arrival");
    

     distance = calculateDistance(departure, arrival);
    printf("Distance between %s and %s: %.2f nm (%.2f km)\n", 
           departure.code, arrival.code,distance * KM_TO_NM, distance);

    return EXIT_SUCCESS;
}
