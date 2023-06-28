#ifndef VEC3_H
#define VEC3_H

#include "Rtweekend.h"
#include <cmath>
#include <iostream>

class Vec3 {
private:
  double e[3];

public:
  Vec3() : e{0, 0, 0} {};
  Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {};

  // for Point3
  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }

  // for Color
  double r() const { return e[0]; }
  double g() const { return e[1]; }
  double b() const { return e[2]; }

  Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
  double operator[](int i) const { return e[i]; }
  double &operator[](int i) { return e[i]; }

  Vec3 &operator+=(const Vec3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }

  Vec3 &operator*=(const double s) {
    e[0] *= s;
    e[1] *= s;
    e[2] *= s;
    return *this;
  }

  Vec3 &operator/=(const double s) { return *this *= 1 / s; }

  double length_squared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }

  double length() const { return std::sqrt(length_squared()); }

  static Vec3 random() {
    return Vec3(random_double(), random_double(), random_double());
  }

  static Vec3 random(double min, double max) {
    return Vec3(random_double(min, max), random_double(min, max),
                random_double(min, max));
  }

  bool near_zero() {
    // return true if this vector is close to zero;
    const double s = 1e-8;
    return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
  }
};

// Type aliases for Vec3
// should probably create classes for them specifically
using Point3 = Vec3; // 3D point
using Color = Vec3;  // RGB color

// Vec3 utility functions
std::ostream &operator<<(std::ostream &os, const Vec3 &v) {
  return os << v[0] << ' ' << v[1] << ' ' << v[2];
}

Vec3 operator+(const Vec3 &u, const Vec3 &v) {
  return Vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

Vec3 operator-(const Vec3 &u, const Vec3 &v) {
  return Vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

Vec3 operator*(const Vec3 &u, const Vec3 &v) {
  return Vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

Vec3 operator*(double s, const Vec3 &v) {
  return Vec3(v[0] * s, v[1] * s, v[2] * s);
}

Vec3 operator*(const Vec3 &u, double s) { return s * u; }

Vec3 operator/(const Vec3 &u, double s) { return u * (1 / s); }

double dot(const Vec3 &u, const Vec3 &v) {
  return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

Vec3 cross(const Vec3 &u, const Vec3 &v) {
  return Vec3(u[1] * v[2] - u[2] * v[1], u[2] * v[0] - u[0] * v[2],
              u[0] * v[1] - u[1] * v[0]);
}

Vec3 unit_vector(Vec3 v) { return v / v.length(); }

Vec3 random_in_unit_sphere() {
  while (true) {
    auto point = Vec3::random(-1, 1);
    if (point.length_squared() >= 1)
      continue;
    return point;
  }
}

Vec3 random_unit_vector() { return unit_vector(random_in_unit_sphere()); }


/// @return The incoming vector reflected across and away from the normal vector
Vec3 reflect(const Vec3 &incoming_vector, const Vec3 &normal) {
  return incoming_vector - 2*dot(incoming_vector, normal)*normal;
}


#endif
