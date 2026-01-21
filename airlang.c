#include <stdio.h>

#define PI 3.14159265358979323846
#define EARTH_RADIUS_KM 6371.0

// Taylor series for sine (radians, up to x^7)
double my_sin(double x) {
    double x3 = x * x * x;
    double x5 = x3 * x * x;
    double x7 = x5 * x * x;
    return x - x3/6.0 + x5/120.0 - x7/5040.0;
}

// Taylor series for cosine (radians, up to x^6)
double my_cos(double x) {
    double x2 = x * x;
    double x4 = x2 * x2;
    double x6 = x4 * x2;
    return 1 - x2/2.0 + x4/24.0 - x6/720.0;
}

// Newton's method for square root
double my_sqrt(double n) {
    if (n < 0) return -1;
    if (n == 0) return 0;
    double x = n;
    for (int i = 0; i < 10; i++) {
        x = 0.5 * (x + n/x);
    }
    return x;
}

// Simple atan2 approximation for small angles
double my_atan2(double y, double x) {
    if (x > 0) return y / x;
    else if (x < 0 && y >= 0) return PI + y / x;
    else if (x < 0 && y < 0) return -PI + y / x;
    else if (x == 0 && y > 0) return PI / 2;
    else if (x == 0 && y < 0) return -PI / 2;
    else return 0; // undefined, but should not happen for our use
}

double toRadians(double degree) {
    return degree * (PI / 180.0);
}

// Haversine formula using custom math functions
double my_haversin(double lat1, double lon1, double lat2, double lon2) {
    double dlat = toRadians(lat2 - lat1);
    double dlon = toRadians(lon2 - lon1);
    double rlat1 = toRadians(lat1);
    double rlat2 = toRadians(lat2);

    double sin_dlat2 = my_sin(dlat / 2.0);
    double sin_dlon2 = my_sin(dlon / 2.0);
    double a = sin_dlat2 * sin_dlat2 +
               my_cos(rlat1) * my_cos(rlat2) *
               sin_dlon2 * sin_dlon2;
    double c = 2 * my_atan2(my_sqrt(a), my_sqrt(1 - a));
    return EARTH_RADIUS_KM * c;
}
void print_file(const char *filename) {
    char line[512];
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open %s for reading.\n", filename);
        return;
    }
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

/*int main(){
   print_file("input.txt");
    return 0;
}*/

int main() {
    double lat1, lon1, lat2, lon2;
    double speed = 0;
    char line[256];

     FILE *file = fopen("input.txt", "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open input.txt for reading.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "Latitude1: %lf", &lat1);
        sscanf(line, "Longitude1: %lf", &lon1);
        sscanf(line, "Latitude2: %lf", &lat2);
        sscanf(line, "Longitude2: %lf", &lon2);
        sscanf(line, "Cruise Speed: %lf", &speed);
    }
    fclose(file);





    /*while (fgets(line, sizeof(line), file)) {
        double temp;
        if (sscanf(line, "Cruise Speed: %lf", &temp) == 1) {
            speed = temp;
            break;
        }
    }
    fclose(file);

    printf("Enter latitude of point 1: ");
    scanf("%lf", &lat1);
    printf("Enter longitude of point 1: ");
    scanf("%lf", &lon1);
    printf("Enter latitude of point 2: ");
    scanf("%lf", &lat2);
    printf("Enter longitude of point 2: ");
    scanf("%lf", &lon2);
    */

     double distance = my_haversin(lat1, lon1, lat2, lon2);
    double time = distance / speed;

    printf("Calculated distance: %.2f km\n", distance);
    printf("Cruise Speed read from file: %.2f km/h\n", speed);
    printf("Estimated travel time: %.2f hours\n", time);

     FILE *outfile = fopen("main.txt", "a");
    if (!outfile) {
        fprintf(stderr, "Error: Could not open main.txt for writing.\n");
        return 1;
    }
    fprintf(outfile, "Latitude1: %.6f\nLongitude1: %.6f\nLatitude2: %.6f\nLongitude2: %.6f\n",
            lat1, lon1, lat2, lon2);
    fprintf(outfile, "Cruise Speed: %.2f km/h\n", speed);
    fprintf(outfile, "Distance: %.2f km\n", distance);
    fprintf(outfile, "Estimated travel time: %.2f hours\n\n", time);
    fclose(outfile);

    printf("Results appended to main.txt\n");






/*
    file = fopen("input.txt", "a");
    if (file) {
        fprintf(file, "Distance: %.2f km\n", distance);
        fprintf(file, "Estimated travel time: %.2f hours\n", time);
        fclose(file);
    }
*/

    return 0;
}









   /* FILE *file = fopen("input.txt", "a");
    
    fprintf(file, "Latitude1: %.6f\nLongitude1: %.6f\nLatitude2: %.6f\nLongitude2: %.6f\n",
            lat1, lon1, lat2, lon2);
    fclose(file);


    double distance = haversine(lat1, lon1, lat2, lon2);
    printf("Calculated distance: %.2f km\n", distance);

     file = fopen("input.txt", "a");
    
    fprintf(file, "Distance: %.2f km\n", distance);

     while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "Cruise Speed: %lf", &speed) == 1) {
            // Found the cruise speed!
            break;
        }
    }
    if (speed <= 0) {
        printf("Cruise Speed not found or invalid in file.\n");
        return 1;
    }
     double time = distance / speed;
      printf("Cruise Speed read from file: %.2f km/h\n", speed);
    printf("Estimated travel time: %.2f hours\n", time);
    fclose(file);


    return 0;
}*/
