#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

// Represents vector equation of a line, P(t) = O + Dt
// where O is the origin, D is the direction, and t is a scalar.
class Ray {
private:
    Point3 mOrigin;
    Vec3 mDirection;
public:
    Ray() {}
    Ray(const Point3 &origin, const Vec3 &direction)
        : mOrigin(origin), mDirection(direction) {}

    Point3 origin() const { return mOrigin; }
    Vec3 direction() const { return mDirection; }

    Point3 at(double t) const {
        return mOrigin + t * mDirection;
    }
};

#endif