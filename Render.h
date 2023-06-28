#include "Camera.h"
#include "Color.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Ray.h"
#include "Rtweekend.h"
#include "Vec3.h"

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

  Color anti_alias(int row, int col, const Camera &camera,
                   const Hittable &world,
                   Color (*ray_color)(const Ray &, const Hittable &, int)) {
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
    return pixel_color;
  }

  void render(const Camera &camera, const Hittable &world,
              Color (*ray_color)(const Ray &, const Hittable &, int)) {

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int row = image_height - 1; row >= 0; row--) {
      std::cerr << "\rScanline remaining: " << row << ' ' << std::flush;
      for (int col = 0; col < image_width; col++) {
        Color pixel_color = anti_alias(row, col, camera, world, ray_color);

        // gamma correction for gamma=2.0
        pixel_color =
            Color(std::sqrt(pixel_color.r()), std::sqrt(pixel_color.g()),
                  std::sqrt(pixel_color.b()));
        write_color(std::cout, pixel_color);
      }
    }
  }

  void render_to_file(const char* file_name, const Camera &camera, const Hittable &world,
              Color (*ray_color)(const Ray &, const Hittable &, int)) {

    init_file(file_name, image_width, image_height);
    
    auto file = std::fstream();
    file.open(file_name);
    if(!file.is_open()) {
        std::cerr << "Failed to open file";
        return;
    }

    for (int row = image_height - 1; row >= 0; row--) {
      std::cerr << "\rScanline remaining: " << row << ' ' << std::flush;
      for (int col = 0; col < image_width; col++) {
        Color pixel_color = anti_alias(row, col, camera, world, ray_color);

        // gamma correction for gamma=2.0
        pixel_color =
            Color(std::sqrt(pixel_color.r()), std::sqrt(pixel_color.g()),
                  std::sqrt(pixel_color.b()));

        int line_to_write_to = 3 + col+1 + (image_height-(row+1))*image_width;
        write_pixel_to_file(file, pixel_color, line_to_write_to);
      }
    }
    file.close();
  }
};
