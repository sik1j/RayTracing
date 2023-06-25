#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cstdlib>
#include <cmath>
#include <limits>
#include <memory>

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

double random_double() {
    // returns double in [0, 1)
    return rand() / (RAND_MAX + 1.0);
}

double random_double(double min, double max) {
    // returns a double in [min, max)
    return random_double()*(max-min) + min;
}

double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

// Common Headers

#include "Ray.h"
#include "Vec3.h"

#endif