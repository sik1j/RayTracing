#include <iostream>

#include "Rtweekend.h"
#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"

Color ray_color(const Ray &ray, const Hittable &world) {
    HitRecord record;
    if (world.hit(ray, 0, infinity, record)) {
        // visualize the normals, (x,y,z) -> (r,g,b)
        return 0.5 * (record.normal + Color(1,1,1));
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

    // World to render
    HittableList world;
    world.add(std::make_shared<Sphere>(Point3(0,0, -1), 0.5));
    world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Camera shoots rays through a viewport through which it computes
    // the colors of each pixel on screen

    // Viewport dimesions
    double viewport_height = 2.0;
    double viewport_width = viewport_height * aspect_ratio;
    double focal_length = 1.0;

    // Camera
    auto camera_origin = Point3(0,0,0); // Camera position
    auto horizontal = Vec3(viewport_width, 0, 0);
    auto vertical = Vec3(0, viewport_height, 0);
    auto lower_left_corner =
        camera_origin - horizontal/2 - vertical/2 - Vec3(0,0,focal_length);

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int row = image_height-1; row >= 0; row--) {
        std::cerr << "\rScanline remaining: " << row << ' ' << std::flush;
        for (int col = 0; col < image_width; col++) {
            // How far along the row and col is as a percentage
            double xPercentage = double(col) / (image_width - 1);
            double yPercentage = double(row) / (image_height - 1);
            // Ray direction points at it's respective x, and y values
            // based on which row and col the img is currently on
            Ray ray(
                camera_origin, 
                lower_left_corner 
                + xPercentage*horizontal 
                + yPercentage*vertical 
                - camera_origin
            );
            Color pixel_color = ray_color(ray, world);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone\n";
}