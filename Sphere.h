#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"
#include "Material.h"
#include "Vec3.h"
#include <memory>

class Sphere : public Hittable {
public:
  Sphere(){};
  Sphere(Point3 center, double radius, std::shared_ptr<Material> material_ptr)
      : center(center), radius(radius), material_ptr(material_ptr){};

  bool hit(const Ray &ray, double t_min, double t_max,
           HitRecord &record) const override;

private:
  Point3 center;
  double radius;
  std::shared_ptr<Material> material_ptr;
};

bool Sphere::hit(const Ray &ray, double t_min, double t_max,
                 HitRecord &record) const {
  Vec3 centerToOrigin = ray.origin() - center;
  double a = ray.direction().length_squared();
  double b = 2 * dot(centerToOrigin, ray.direction());
  double c = centerToOrigin.length_squared() - radius * radius;

  double discriminant = b * b - 4 * a * c;
  if (discriminant < 0) {
    return false;
  }
  double sqrtDiscriminant = std::sqrt(discriminant);

  // Find the nearest root within range [t_min, t_max]
  double root = (-b - sqrtDiscriminant) / (2 * a);

  if (root < t_min || root > t_max) {
    root = (-b + sqrtDiscriminant) / (2 * a);
    if (root < t_min || root > t_max) {
      return false;
    }
  }

  record.t = root;
  record.point = ray.at(record.t);
  Vec3 outward_normal = (record.point - center) / radius;
  record.set_face_normal(ray, outward_normal);
  record.material_ptr = material_ptr;

  return true;
}

#endif
