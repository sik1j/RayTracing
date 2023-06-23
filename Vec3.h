#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class Vec3 {
private:
    double e[3];
public:    
    Vec3() : e{0,0,0} {};
    Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {};
    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    Vec3& operator+=(const Vec3 &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    Vec3& operator*=(const double s) {
        e[0] *= s;
        e[1] *= s;
        e[2] *= s;
    }

    Vec3& operator/=(const double s) {
        return *this *= 1/s;
    }

    double length_squared() const {
        return dot(*this, *this);
    }

    double length() const {
        return std::sqrt(length_squared());
    }

};

// Type aliases for Vec3
// should probably create classes for them specifically
using Point3 = Vec3; // 3D point
using Color = Vec3; // RGB color

// Vec3 utility functions
std::ostream& operator<<(std::ostream &os, const Vec3 &v) {
    return os << v[0] << ' ' << v[1] << ' ' << v[2];
}

Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(
        u[0] + v[0],
        u[1] + v[1],
        u[2] + v[2]
    );
}

Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(
        u[0] - v[0],
        u[1] - v[1],
        u[2] - v[2]
    );
}

Vec3 operator*(const Vec3 &u, const Vec3 &v) {
    return Vec3(
        u[0] * v[0],
        u[1] * v[1],
        u[2] * v[2]
    );
}

Vec3 operator*(int s, const Vec3 &v) {
    return Vec3(
        v[0] * s,
        v[1] * s,
        v[2] * s
    );
}

Vec3 operator*(const Vec3 &u, int s) {
    return s * u;
}

Vec3 operator/(const Vec3 &u, int s) {
    return u * (1/s);
}

double dot(const Vec3 &u, const Vec3 &v) {
    return u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
}

Vec3 cross(const Vec3 &u, const Vec3 &v) {
    return Vec3(
        u[1] * v[2] - u[2] * v[1],
        u[2] * v[0] - u[0] * v[2],
        u[0] * v[1] - u[1] * v[0]
    );
}

Vec3 unit_vector(Vec3 v) {
    return v / v.length();
}

#endif