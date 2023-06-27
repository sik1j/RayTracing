#include "Camera.h"
#include "Color.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Ray.h"
#include "Rtweekend.h"
#include <iostream>

class Render {
private:
  const double aspect_ratio;
  const int image_width;
  const int image_height;
  const int samples_per_pixel;
  const int max_depth;

public:
  Render();
  Render(double aspect_ratio, int image_width, int image_height,
         int samples_per_pixel, int max_depth)
      : aspect_ratio(aspect_ratio), image_width(image_width),
        image_height(image_height), samples_per_pixel(samples_per_pixel),
        max_depth(max_depth){};

  void render(const Camera &camera, const Hittable &world,
              Color (*ray_color)(const Ray&, const Hittable&, int)) {

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int row = image_height - 1; row >= 0; row--) {
      std::cerr << "\rScanline remaining: " << row << ' ' << std::flush;
      for (int col = 0; col < image_width; col++) {
        Color pixel_color = Color(0, 0, 0);
        // anti-aliasing
        // slightly varys rays per pixel, and takes avg of all rays as color
        for (int s = 0; s < samples_per_pixel; s++) {
          // How far along the row and col is as a
          // fraction of width and height respectively
          double u = double(col + random_double()) / (image_width - 1);
          double v = double(row + random_double()) / (image_height - 1);

          Ray ray = camera.get_ray(u, v);
          pixel_color += ray_color(ray, world, max_depth);
        }
        pixel_color /= samples_per_pixel;
        // gamma correction for gamma=2.0
        pixel_color =
            Color(std::sqrt(pixel_color.r()), std::sqrt(pixel_color.g()),
                  std::sqrt(pixel_color.b()));
        write_color(std::cout, pixel_color);
      }
    }
  }
};
