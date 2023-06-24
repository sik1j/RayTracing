#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "Hittable.h"

#include <memory>
#include <vector>

class HittableList : public Hittable
{
private:
    std::vector<std::shared_ptr<Hittable>> geometries;
public:
    HittableList() {};
    HittableList(std::shared_ptr<Hittable> geometry) { add(geometry); }

    void clear() { geometries.clear(); }
    void add(std::shared_ptr<Hittable> geometry) { 
        geometries.push_back(geometry); 
    }
    
    bool hit(
        const Ray &ray, double t_min, double t_max, HitRecord &record
    ) const override;
};

bool HittableList::hit(
    const Ray &ray, double t_min, double t_max, HitRecord &record
) const {
    HitRecord temp_record;
    bool hit_anything = false;
    double closest_so_far = t_max;

    for (const auto &geometry : geometries) {
        if (geometry->hit(ray, t_min, closest_so_far, temp_record)) {
            hit_anything = true;
            closest_so_far = temp_record.t;
            record = temp_record;
        }
    }

    return hit_anything;
}



#endif
