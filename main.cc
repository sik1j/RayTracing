#include <iostream>

#include "Color.h"
#include "Vec3.h"
#include "Ray.h"

Color ray_color(const Ray &ray) {
    Vec3 unit_direction = unit_vector(ray.direction());
    double t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
}


int main() {
    // Image Dimensions
    const double aspect_ratio = 16.0/9.0;
    const int image_width = 400;
    const int image_height = int(image_width / aspect_ratio);

    // Camera shoots rays through a viewport through which it computes
    // the colors of each pixel on screen
    // Viewport dimesions
    double viewport_height = 2.0;
    double viewport_width = viewport_height * aspect_ratio;
    double focal_length = 1.0;

    // Camera
    auto origin = Point3(0,0,0); // Camera position
    auto horizontal = Vec3(viewport_width, 0, 0);
    auto vertical = Vec3(0, viewport_height, 0);
    auto lower_left_corner =
        origin - horizontal/2 - vertical/2 - Vec3(0,0,focal_length);

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // green decreases as row's increase
    for (int row = image_height-1; row >= 0; row--) {
        std::cerr << "\rScanline remaining: " << row << ' ' << std::flush;
        // red increases as col's increase
        for (int col = 0; col < image_width; col++) {
            // linearly maps: [0, image_dimension-1] -> [0, 1]
            Color pixel_color(
                (double)row/(image_height - 1),
                (double)col/(image_width - 1),
                0.25
            );

            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone\n";
}