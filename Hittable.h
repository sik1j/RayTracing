#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"


/// @brief Records the closest hit point for some ray and geometry
struct HitRecord {
    /// @brief The point that was hit
    Point3 point;
    /// @brief The normal between ray, P(t), and the geometry. 
    // Always points oppositeto the ray
    Vec3 normal;
    /// @brief Scalar at which ray, P(t), hit the geometry
    double t;
    /// @brief if the hit is on the front face of the geometry
    bool is_front_face;

    void set_face_normal(const Ray &ray, const Vec3 &outward_normal) {
        is_front_face = dot(ray.direction(), outward_normal) < 0;
        normal = is_front_face ? outward_normal : -outward_normal;
    }
};


/// @brief Abstract class to implement on a hittable geometry such as a
// sphere, or plane, etc.
class Hittable {
public:
    /// @brief Determines if @p ray, P(t), intersects self and records it in 
    //  [record] if t in range [t_min, t_max]
    /// @param[in] ray the ray to check intersection with
    /// @param[in] t_min minimum t value that counts as an intersection
    /// @param[in] t_max maximum t value that counts as an intersection
    /// @param[out] record object to record hit data in. if multiple hits, 
    // stores the closest hit
    /// @return true if 1 or more hits, else false
    virtual bool hit(
        const Ray &ray, double t_min, double t_max, HitRecord &record
    ) const = 0;
};

#endif