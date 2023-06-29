#ifndef HITTABLE_H
#define HITTABLE_H

#include "Material.h"
#include "Ray.h"
#include <memory>


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
  virtual bool hit(const Ray &ray, double t_min, double t_max,
                   HitRecord &record) const = 0;
};

#endif
