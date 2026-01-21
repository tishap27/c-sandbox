#include <stdio.h>

#define AIRPORTS 5
#define INF 99999

const char *airportNames[AIRPORTS] = {"YYZ", "YVR", "YUL", "YYC", "YOW"};

// Adjacent matrix distance between airports starting point YYZ

int flightMap[AIRPORTS][AIRPORTS] = {
    {0, 1760, 271, 1495, 187},  // YYZ
    {1760, 0, 1973, 337, 1919}, // YVR
    {271, 1973, 0, 1575, 151},  // YUL
    {1495, 337, 1575, 0, 1405}, // YYC
    {187, 1919, 151, 1405, 0}   // YOW
};

int min_distance(int distance[], int visited[]) {
    int min = INF, min_index = -1;
    for (int i = 0; i < AIRPORTS; i++) {
        if (!visited[i] && distance[i] <= min) {
            min = distance[i];
            min_index = i;
        }
    }
    return min_index;
}

void dijkstra(int src) {
    int distance[AIRPORTS];
    int visited[AIRPORTS];
    int parent[AIRPORTS];
    for (int i = 0; i < AIRPORTS; i++) {
        distance[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }
    distance[src] = 0;
    
    for (int count = 0; count < AIRPORTS-1; count++) {
        int u = min_distance(distance, visited);
        visited[u] = 1;
        for (int v = 0; v < AIRPORTS; v++) {
            if (!visited[v] && flightMap[u][v] && distance[u] + flightMap[u][v] < distance[v]) {
                parent[v] = u;
                distance[v] = distance[u] + flightMap[u][v];
            }
        }
    }
    printf("Shortest distances from %s:\n", airportNames[src]);
    for (int i = 0; i < AIRPORTS; i++) {
        printf("To %s: %d nautical miles\n", airportNames[i], distance[i]);
    }
}

int main() {
    int source = 0; // YYZ
    dijkstra(source);
    return 0;
}