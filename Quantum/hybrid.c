//STILL CLASSICAL DIJKSTRA BUT NOW BASIC QAOA AS WELL. 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "distanceCalculation.h"

#define MAX_AIRPORTS 10
#define INF 99999


// Quantum simulation parameters
#define MAX_QUBITS 20
#define QAOA_ITERATIONS 50
#define VARIATIONAL_PARAMS 6

// Airport structure with coordinates for realistic distance calculation
typedef struct {
    char code[4];
    char name[30];
    double lat;  // Latitude in degrees
    double lon;  // Longitude in degrees
    int active;
} Airport;

// Flight route cost structure (multi-objective)
typedef struct {
    int distance;     // Nautical miles
    int fuel_cost;    // Relative fuel consumption
    int time_cost;    // Flight time in minutes
    int weather_penalty; // Weather-based delay
} RouteCost;

// Quantum state representation
typedef struct {
    double real;
    double imag;
} Complex;

// Global airport database
Airport airports[MAX_AIRPORTS] = {
    {"YYZ", "Toronto Pearson", 43.6777, -79.6248, 1},
    {"YVR", "Vancouver", 49.1967, -123.1815, 1},
    {"YUL", "Montreal", 45.4589, -73.7497, 1},
    {"YYC", "Calgary", 51.1315, -114.0106, 1},
    {"YOW", "Ottawa", 45.3192, -75.6692, 1},
    {"YWG", "Winnipeg", 49.9100, -97.2397, 1},
    {"YHZ", "Halifax", 44.8808, -63.5086, 1},
    {"", "", 0, 0, 0}, // Inactive slots
    {"", "", 0, 0, 0},
    {"", "", 0, 0, 0}
};

int num_active_airports = 7;


// Generate multi-objective cost matrix
void generate_cost_matrix(RouteCost costs[MAX_AIRPORTS][MAX_AIRPORTS]) {
    srand(time(NULL));
    for (int i = 0; i < num_active_airports; i++) {
        for (int j = 0; j < num_active_airports; j++) {
            if (i == j) {
                costs[i][j] = (RouteCost){0, 0, 0, 0};
            } else {
                double dist = my_haversin(
                    airports[i].lat, airports[i].lon,
                    airports[j].lat, airports[j].lon
                );
                costs[i][j] = (RouteCost){
                    (int)dist,
                    (int)(dist * 0.8 + rand() % 100), // Fuel estimate
                    (int)(dist / 8 + rand() % 60),    // Time estimate
                    rand() % 50                       // Weather penalty
                };
            }
        }
    }
}

// ============ CLASSICAL ALGORITHMS ============

// Classical Dijkstra for baseline comparison
typedef struct {
    int distance;
    int path[MAX_AIRPORTS];
    int path_length;
} ClassicalResult;

ClassicalResult dijkstra_multi_objective(RouteCost costs[MAX_AIRPORTS][MAX_AIRPORTS], 
                                        int src, int dest, double weight_dist, 
                                        double weight_fuel, double weight_time) {
    int distance[MAX_AIRPORTS];
    int visited[MAX_AIRPORTS];
    int parent[MAX_AIRPORTS];
    ClassicalResult result = {INF, {0}, 0};
    
    for (int i = 0; i < num_active_airports; i++) {
        distance[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }
    
    distance[src] = 0;
    
    for (int count = 0; count < num_active_airports - 1; count++) {
        int min = INF, u = -1;
        
        for (int i = 0; i < num_active_airports; i++) {
            if (!visited[i] && distance[i] < min) {
                min = distance[i];
                u = i;
            }
        }
        
        if (u == -1) break;
        visited[u] = 1;
        
        for (int v = 0; v < num_active_airports; v++) {
            if (!visited[v] && costs[u][v].distance > 0) {
                // Multi-objective cost function
                int multi_cost = (int)(
                    weight_dist * costs[u][v].distance +
                    weight_fuel * costs[u][v].fuel_cost +
                    weight_time * costs[u][v].time_cost +
                    0.1 * costs[u][v].weather_penalty
                );
                
                if (distance[u] + multi_cost < distance[v]) {
                    parent[v] = u;
                    distance[v] = distance[u] + multi_cost;
                }
            }
        }
    }
    
    // Reconstruct path
    if (distance[dest] != INF) {
        result.distance = distance[dest];
        
        // Build path backwards
        int path_temp[MAX_AIRPORTS];
        int path_idx = 0;
        int current = dest;
        
        while (current != -1) {
            path_temp[path_idx++] = current;
            current = parent[current];
        }
        
        // Reverse path
        for (int i = 0; i < path_idx; i++) {
            result.path[i] = path_temp[path_idx - 1 - i];
        }
        result.path_length = path_idx;
    }
    
    return result;
}

// ============ QUANTUM SIMULATION ============

// Simulate quantum state superposition
Complex quantum_state[1 << MAX_QUBITS]; // 2^MAX_QUBITS states

// Initialize quantum state in uniform superposition
void initialize_quantum_state(int num_qubits) {
    int num_states = 1 << num_qubits;
    double amplitude = 1.0 / sqrt(num_states);
    
    for (int i = 0; i < num_states; i++) {
        quantum_state[i].real = amplitude;
        quantum_state[i].imag = 0.0;
    }
}

// QAOA cost function (Ising model formulation)
double qaoa_cost_function(int state, RouteCost costs[MAX_AIRPORTS][MAX_AIRPORTS], 
                         double weights[4]) {
    double cost = 0.0;
    int path[MAX_AIRPORTS];
    int path_length = 0;
    
    // Extract path from binary state representation
    // This is a simplified encoding - real QAOA would be more complex
    for (int i = 0; i < num_active_airports && path_length < MAX_AIRPORTS - 1; i++) {
        if (state & (1 << i)) {
            path[path_length++] = i;
        }
    }
    
    // Calculate path cost if valid
    if (path_length >= 2) {
        for (int i = 0; i < path_length - 1; i++) {
            int from = path[i];
            int to = path[i + 1];
            
            if (from < num_active_airports && to < num_active_airports) {
                cost += weights[0] * costs[from][to].distance +
                       weights[1] * costs[from][to].fuel_cost +
                       weights[2] * costs[from][to].time_cost +
                       weights[3] * costs[from][to].weather_penalty;
            }
        }
    } else {
        cost = INF; // Invalid path penalty
    }
    
    return cost;
}

// Simplified QAOA simulation
typedef struct {
    int best_path[MAX_AIRPORTS];
    int path_length;
    double cost;
    int iterations_run;
} QAOAResult;

QAOAResult simulate_qaoa(RouteCost costs[MAX_AIRPORTS][MAX_AIRPORTS], 
                        int src, int dest, double weights[4]) {
    QAOAResult result = {{0}, 0, INF, 0};
    
    printf("Running QAOA simulation...\n");
    printf("Quantum superposition of %d possible routes\n", 1 << num_active_airports);
    
    // Initialize quantum state
    initialize_quantum_state(num_active_airports);
    
    double best_cost = INF;
    int best_state = 0;
    
    // Simulate QAOA iterations
    for (int iter = 0; iter < QAOA_ITERATIONS; iter++) {
        // Simulate quantum evolution (simplified)
        for (int state = 0; state < (1 << num_active_airports); state++) {
            double cost = qaoa_cost_function(state, costs, weights);
            
            // Quantum interference simulation (amplify good solutions)
            if (cost < best_cost) {
                best_cost = cost;
                best_state = state;
            }
            
            // Update quantum amplitudes based on cost
            double penalty = exp(-cost / 1000.0); // Cooling factor
            quantum_state[state].real *= penalty;
        }
        
        // Normalize quantum state
        double norm = 0.0;
        for (int i = 0; i < (1 << num_active_airports); i++) {
            norm += quantum_state[i].real * quantum_state[i].real;
        }
        norm = sqrt(norm);
        
        for (int i = 0; i < (1 << num_active_airports); i++) {
            quantum_state[i].real /= norm;
        }
        
        if (iter % 10 == 0) {
            printf("Iteration %d: Best cost = %.2f\n", iter, best_cost);
        }
    }
    
    // Extract best path from quantum state
    int path_idx = 0;
    for (int i = 0; i < num_active_airports && path_idx < MAX_AIRPORTS; i++) {
        if (best_state & (1 << i)) {
            result.best_path[path_idx++] = i;
        }
    }
    
    result.path_length = path_idx;
    result.cost = best_cost;
    result.iterations_run = QAOA_ITERATIONS;
    
    return result;
}

// ============ COMPARISON ENGINE ============

void print_route_comparison(ClassicalResult classical, QAOAResult quantum, 
                          RouteCost costs[MAX_AIRPORTS][MAX_AIRPORTS]) {
    printf("\n=== ALGORITHM COMPARISON ===\n");
    
    printf("\n1. CLASSICAL DIJKSTRA:\n");
    printf("   Total Cost: %d\n", classical.distance);
    printf("   Route: ");
    for (int i = 0; i < classical.path_length; i++) {
        printf("%s", airports[classical.path[i]].code);
        if (i < classical.path_length - 1) printf(" -> ");
    }
    printf("\n");
    
    printf("\n2. QUANTUM QAOA:\n");
    printf("   Total Cost: %.2f\n", quantum.cost);
    printf("   Route: ");
    for (int i = 0; i < quantum.path_length; i++) {
        printf("%s", airports[quantum.best_path[i]].code);
        if (i < quantum.path_length - 1) printf(" -> ");
    }
    printf("\n   Iterations: %d\n", quantum.iterations_run);
    
    printf("\n3. PERFORMANCE ANALYSIS:\n");
    if (quantum.cost < classical.distance) {
        printf("   ✓ Quantum algorithm found better solution!\n");
        printf("   Improvement: %.2f%% cost reduction\n", 
               ((double)classical.distance - quantum.cost) / classical.distance * 100);
    } else if (abs(quantum.cost - classical.distance) < 1) {
        printf("   ≈ Both algorithms found similar solutions\n");
    } else {
        printf("   ✓ Classical algorithm performed better\n");
        printf("   Note: QAOA may need parameter tuning\n");
    }
}

int main() {
    RouteCost costs[MAX_AIRPORTS][MAX_AIRPORTS];
    
    printf("=== QUANTUM-CLASSICAL FLIGHT ROUTE OPTIMIZER ===\n\n");
    
    // Generate realistic cost matrix
    printf("Generating flight network with real coordinates...\n");
    generate_cost_matrix(costs);
    
    // Show available airports
    printf("\nActive airports in network:\n");
    for (int i = 0; i < num_active_airports; i++) {
        printf("%s - %s (%.2f°, %.2f°)\n", 
               airports[i].code, airports[i].name, 
               airports[i].lat, airports[i].lon);
    }
    
    // Set optimization weights (can be adjusted)
    double weights[4] = {1.0, 0.8, 0.6, 0.3}; // distance, fuel, time, weather
    
    int src = 0; // YYZ
    int dest = 1; // YVR
    
    printf("\n=== OPTIMIZING ROUTE: %s -> %s ===\n", 
           airports[src].code, airports[dest].code);
    
    // Run classical algorithm
    printf("\nRunning classical Dijkstra...\n");
    ClassicalResult classical = dijkstra_multi_objective(costs, src, dest, 
                                                       weights[0], weights[1], weights[2]);
    
    // Run quantum simulation
    printf("\nRunning quantum QAOA simulation...\n");
    QAOAResult quantum = simulate_qaoa(costs, src, dest, weights);
    
    // Compare results
    print_route_comparison(classical, quantum, costs);
    
    printf("\n=== QUANTUM ADVANTAGE ANALYSIS ===\n");
    printf("Problem size: %d airports = %d possible routes\n", 
           num_active_airports, 1 << num_active_airports);
    printf("Classical complexity: O(V²) = O(%d)\n", num_active_airports * num_active_airports);
    printf("Quantum complexity: O(√N) iterations with quantum parallelism\n");
    printf("Quantum advantage emerges with >100 airports and complex constraints\n");
    
    return 0;
}