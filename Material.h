#ifndef MATERIAL_H
#define MATERIAL_H

#include "Ray.h"
#include "Rtweekend.h"
#include "Vec3.h"

struct HitRecord;

class Material {
public:
  virtual bool scatter(const Ray &ray_in, const HitRecord &record,
                       Color &attenuation, Ray &scattered) = 0;
};

#endif
