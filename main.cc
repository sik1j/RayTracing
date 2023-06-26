#include <iostream>

#include "Rtweekend.h"
#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Vec3.h"

Color ray_color(const Ray &ray, const Hittable &world, int depth) {
    // recursion limit to proctect the stack from blowing up
    if (depth <= 0) {
        return Color(0,0,0);
    }

    HitRecord record;
    // recursively define diffuse coloring when recording a hit.
    // After a hit, chooses random direction to reflect ray towards
    // ray accumulates colors from all it's hits
    if (world.hit(ray, 0, infinity, record)) {
        // random point outside the surface inside a unit sphere
        Point3 target = record.point + record.normal + random_unit_vector(); 
        // visualize the normals, (x,y,z) -> (r,g,b)
        return 0.5  * ray_color(
            Ray(record.point, target - record.point), 
            world, depth-1
        );
    }

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
    world.add(std::make_shared<Sphere>(Point3(0,0, -1), 0.5));
    world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Camera
    auto camera = Camera();

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int row = image_height-1; row >= 0; row--) {
        std::cerr << "\rScanline remaining: " << row << ' ' << std::flush;
        for (int col = 0; col < image_width; col++) {
            Color pixel_color = Color(0,0,0);
            // anti-aliasing
            // slightly varys rays per pixel, and takes avg of all rays as color
            for (int s = 0; s < samples_per_pixel; s++) {
                // How far along the row and col is as a 
                // fraction of width and height respectively
                double u = double(col + random_double()) / (image_width - 1);
                double v = double(row + random_double()) / (image_height - 1);

                Ray ray = camera.get_ray(u,v);
                pixel_color += ray_color(ray, world, max_depth);
            }
            pixel_color /= samples_per_pixel;
            // gamma correction for gamma=2.0
            pixel_color = Color(
                std::sqrt(pixel_color.r()),
                std::sqrt(pixel_color.g()),
                std::sqrt(pixel_color.b())
            );
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone\n";
}
