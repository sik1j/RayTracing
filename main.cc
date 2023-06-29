#include <iostream>
#include <chrono>

#include "Rtweekend.h"
#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Vec3.h"
#include "Render.h"
#include "Material.h"
#include "HitRecord.h"

Color ray_color(const Ray &ray, const Hittable &world, int depth) {
    // recursion limit to proctect the stack from blowing up
    if (depth <= 0) {
        return Color(0,0,0);
    }

    HitRecord record;

    if (world.hit(ray, 0, infinity, record)) {
        Ray scattered;
        Color attenuation;
        
        if (record.material_ptr->scatter(ray, record, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, depth-1);
        }
        // if ray absorbed
        return Color(0,0,0);
   }

    // background color when no hit

    // normalize vector 
    Vec3 unit_direction = unit_vector(ray.direction());
    // map it's y val from [-1.0, 1.0] -> [0, 1.0], 
    // as LERP only takes t vals in [0,1.0]
    double t = 0.5*(unit_direction.y() + 1.0);
    // lerp between white to sky blue
    return (1.0-t)*Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
}


int main() {
    // Image Dimensions
    const double aspect_ratio = 16.0/9.0;
    const int image_width = 400;
    const int image_height = int(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // World to render
    HittableList world;

    auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
    auto material_left   = std::make_shared<Metal>(Color(0.8, 0.8, 0.8));
    auto material_right  = std::make_shared<Metal>(Color(0.8, 0.6, 0.2));

    world.add(std::make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(Point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(std::make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(std::make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.5, material_right));

    // Camera
    auto camera = Camera();


    auto start = std::chrono::high_resolution_clock::now();
    // Render
    Render renderer(aspect_ratio, image_width, image_height, 
            samples_per_pixel, max_depth);

    renderer.render(camera, world, ray_color);
    
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop-start).count();

    std::cerr << "\nDone in " << duration << " seconds\n";
}
