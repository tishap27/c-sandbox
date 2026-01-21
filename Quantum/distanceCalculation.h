// distanceCalculation.h

#ifndef DISTANCECALCULATION_H
#define DISTANCECALCULATION_H

#define PI 3.14159265358979323846
#define EARTH_RADIUS_NM 3440.065  // In nautical miles

// Taylor series for sine (radians, up to x^7)
static inline double my_sin(double x) {
    double x3 = x * x * x;
    double x5 = x3 * x * x;
    double x7 = x5 * x * x;
    return x - x3/6.0 + x5/120.0 - x7/5040.0;
}

// Taylor series for cosine (radians, up to x^6)
static inline double my_cos(double x) {
    double x2 = x * x;
    double x4 = x2 * x2;
    double x6 = x4 * x2;
    return 1 - x2/2.0 + x4/24.0 - x6/720.0;
}

// Newton's method for square root
static inline double my_sqrt(double n) {
    if (n < 0) return -1;
    if (n == 0) return 0;
    double x = n;
    for (int i = 0; i < 10; i++) {
        x = 0.5 * (x + n/x);
    }
    return x;
}

// Simple atan2 approximation for small angles
static inline double my_atan2(double y, double x) {
    if (x > 0) return y / x;
    else if (x < 0 && y >= 0) return PI + y / x;
    else if (x < 0 && y < 0) return -PI + y / x;
    else if (x == 0 && y > 0) return PI / 2;
    else if (x == 0 && y < 0) return -PI / 2;
    else return 0;
}

static inline double toRadians(double degree) {
    return degree * (PI / 180.0);
}

// Haversine formula using custom math functions, returns distance in nautical miles
static inline double my_haversin(double lat1, double lon1, double lat2, double lon2) {
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
    return EARTH_RADIUS_NM * c; // result in nautical miles
}

#endif // DISTANCECALCULATION_H
