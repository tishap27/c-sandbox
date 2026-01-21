#include <stdio.h>
#include <stdlib.h>
#include "optimizer_bridge.h"

int main() {
    printf("Quantum Optimized Flight Plan (C main)\n");

    // Write flight plan parameters to input.txt
    FILE *fp = fopen("../data/input.txt", "w");
    if (!fp) {
        perror("Failed to open input.txt");
        return 1;
    }
    fprintf(fp, "Departure: CYOW\nArrival: CYYZ\nAltitude: 9000\n");
    fclose(fp);

    // Call Ada optimizer (simulate by running system command)
    run_ada_optimizer();

    // Read optimized result from output.txt
    fp = fopen("../data/output.txt", "r");
    if (!fp) {
        perror("Failed to open output.txt");
        return 1;
    }
    char line[128];
    printf("Optimized Flight Plan Output (from Ada):\n");
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    fclose(fp);
    return 0;
}
