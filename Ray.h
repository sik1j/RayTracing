#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

// Represents vector equation of a line, P(t) = O + Dt
// where O is the origin, D is the direction, and t is a scalar.
class Ray {
private:
    Point3 origin;
    Vec3 direction;
public:
    Ray() {}
    Ray(const Point3 &origin, const Vec3 &direction)
        : origin(origin), direction(direction) {}

    Point3 origin() const { return origin; }
    Vec3 direction() const { return direction; }

    Point3 at(double t) {
        return origin + t * direction;
    }
}

#endif