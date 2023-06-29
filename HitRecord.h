#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include "Vec3.h"
#include <memory>
#include "Material.h"

class Material;

/// @brief Records the closest hit point for some ray and geometry
struct HitRecord {
  /// @brief Point that was hit
  Point3 point;
  /// @brief Normal between ray, P(t), and geometry.
  // Normalized and points opposite to the ray.
  Vec3 normal;
  std::shared_ptr<Material> material_ptr;
  /// @brief Scalar at which ray, P(t), hit the geometry
  double t;
  /// @brief if the hit is on the front face of the geometry
  bool is_front_face;

  void set_face_normal(const Ray &ray, const Vec3 &outward_normal) {
    is_front_face = dot(ray.direction(), outward_normal) < 0;
    normal = is_front_face ? outward_normal : -outward_normal;
  }
};

#endif