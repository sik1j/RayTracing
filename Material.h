#ifndef MATERIAL_H
#define MATERIAL_H

#include "Ray.h"
#include "Rtweekend.h"
#include "Hittable.h"
#include "HitRecord.h"
#include "Vec3.h"

class Material
{
public:
  /// @return false if ray was absorbed
  virtual bool scatter(const Ray &ray_in, const HitRecord &record,
                       Color &attenuation, Ray &scattered) const = 0;
};

class Lambertian : public Material
{
private:
  // the amount of light reflected by surface
  Color albedo;

public:
  Lambertian(const Color &albedo) : albedo(albedo){};

  bool scatter(const Ray &ray_in, const HitRecord &record, Color &attenuation,
               Ray &scattered) const override
  {
    auto scatter_direction = record.normal + random_unit_vector();
    scattered = Ray(record.point, scatter_direction);

    // if random_unit_vector happens to be opposite to record.normal
    if (scatter_direction.near_zero())
    {
      scatter_direction = record.normal;
    }

    attenuation = albedo;
    return true;
  }
};

class Metal : public Material
{
private:
  // the amount of light reflected by surface
  Color albedo;
  // how (un)clear the reflection is
  double fuzz;

public:
  Metal(const Color &albedo, double fuzz) : albedo(albedo), fuzz(fuzz) {};

  bool scatter(const Ray &ray_in, const HitRecord &record, Color &attenuation,
               Ray &scattered) const override
  {
    Vec3 reflected = reflect(unit_vector(ray_in.direction()), record.normal);
    scattered = Ray(record.point, reflected + fuzz*random_in_unit_sphere());
    attenuation = albedo;
    return (dot(scattered.direction(), record.normal) > 0);
  }
};

#endif
