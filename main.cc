#include <iostream>

#include "Color.h"
#include "Vec3.h"
#include "Ray.h"

/// @brief Determine if a ray intersects sphere
/// @param center Coords of sphere's center
/// @param radius Radius of given sphere
/// @param ray Ray to test intersection with
/// @return Whether the ray intersects the sphere or not
bool hit_sphere(const Point3 &center, double radius, const Ray &ray) {
    // Given the vector equation of a sphere centered at C of radius r,
    // dot(P(t)-C, P(t)-C) = r^2, where P(t) is the point that hits the sphere
    // this expands into a quadratic, and we solve for t.
    // If to check for hits

    Vec3 centerToOrigin = ray.origin() - center;
    double a = dot(ray.direction(), ray.direction());
    double b = 2.0 * dot(ray.direction(), centerToOrigin);
    double c = dot(centerToOrigin, centerToOrigin) - radius*radius;

    // determines if the sphere is hit or not
    double discriminant = b*b - 4*a*c;
    // hit if non-negative
    return discriminant >= 0;
}

// returns a lerp between white to sky blue based on the y value
Color ray_color(const Ray &ray) {
    // sphere of radius 0.5 at (0,0,-1)
    if (hit_sphere(Point3(0,0,-1), 0.5, ray)) {
        return Color(1.0, 0, 0);
    }
    // normalize the y value 
    Vec3 unit_direction = unit_vector(ray.direction());
    // map it from [-1.0, 1.0] to [0, 1.0], as LERP only takes t vals in [0,1.0]
    double t = 0.5*(unit_direction.y() + 1.0);
    // lerp between white to sky blue
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
            write_color(std::cout, ray_color(ray));
        }
    }

    std::cerr << "\nDone\n";
}