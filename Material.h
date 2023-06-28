#ifndef MATERIAL_H
#define MATERIAL_H

#include "Ray.h"
#include "Rtweekend.h"
#include "Vec3.h"

struct HitRecord;

class Material {
public:
  virtual bool scatter(const Ray &ray_in, const HitRecord &record,
                       Color &attenuation, Ray &scattered) const = 0;
};

class Lambertian : public Material {
private:
  // the amount of light reflected by surface
  Color albedo;

public:
  Lambertian(const Color &albedo) : albedo(albedo){};

  bool scatter(const Ray &ray_in, const HitRecord &record, Color &attenuation,
               Ray &scattered) const override {
    auto scatter_direction = record.normal + random_unit_vector();
    scattered = ray(record.p, scatter_direction);

    // if random_unit_vector happens to be opposite to record.normal
    if (scatter_direction.near_zero()) {
      scatter_direction = record.normal;
    }

    attenuation = albedo;
    return true;
  }
};

#endif
