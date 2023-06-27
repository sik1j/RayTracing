#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"
#include "Rtweekend.h"
#include "Vec3.h"

class Camera {
private:
    Point3 origin;
    Point3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
public:
    Camera() {
        // Viewport
        const double aspect_ratio = 16.0/9.0;
        double viewport_height = 2.0;
        double viewport_width = viewport_height * aspect_ratio;
        double focal_length = 1.0;

        // Camera
        origin = Point3(0,0,0); 
        horizontal = Vec3(viewport_width, 0, 0);
        vertical = Vec3(0, viewport_height, 0);
        lower_left_corner =
            origin - horizontal/2 - vertical/2 - Vec3(0,0,focal_length);
    };

    /// @brief
    /// @param u fraction of image width: x / image_width
    /// @param v fraction of iamge height: y / image_height
    /// @return ray given the current viewport coords
    Ray get_ray(double u, double v) const {
        return Ray(
            origin,
            lower_left_corner 
            + u*horizontal 
            + v*vertical 
            - origin
        );
    }
};

#endif
