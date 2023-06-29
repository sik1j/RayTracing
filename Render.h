#include "Camera.h"
#include "Color.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Ray.h"
#include "Rtweekend.h"
#include "Vec3.h"

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

typedef Color (*RayColorFunc)(const Ray &, const Hittable &, int);

class Render
{
private:
  const double aspect_ratio;
  const int image_width;
  const int image_height;
  const int samples_per_pixel;
  const int max_depth;
  const Camera &camera;
  const Hittable &world;
  RayColorFunc ray_color;
  std::mutex mtx;

public:
  Render();
  Render(double aspect_ratio, int image_width, int image_height,
         int samples_per_pixel, int max_depth, Camera &camera, Hittable &world,
         Color (*ray_color)(const Ray &, const Hittable &, int))
      : aspect_ratio(aspect_ratio), image_width(image_width),
        image_height(image_height), samples_per_pixel(samples_per_pixel),
        max_depth(max_depth), camera(camera), world(world),
        ray_color(ray_color){};

  Color anti_alias(int row, int col)
  {
    Color pixel_color = Color(0, 0, 0);

    // anti-aliasing
    // slightly varys rays per pixel, and takes avg of all rays as color
    for (int s = 0; s < samples_per_pixel; s++)
    {
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

  void render_to_cout()
  {

    std::cout << "P3\n"
              << image_width << ' ' << image_height << "\n255\n";

    for (int row = image_height - 1; row >= 0; row--)
    {
      std::cerr << "\rScanline remaining: " << row << ' ' << std::flush;
      for (int col = 0; col < image_width; col++)
      {
        Color pixel_color = anti_alias(row, col);

        // gamma correction for gamma=2.0
        pixel_color =
            Color(std::sqrt(pixel_color.r()), std::sqrt(pixel_color.g()),
                  std::sqrt(pixel_color.b()));
        write_color(std::cout, pixel_color);
      }
    }
  }

  void render_to_file(const char *file_name)
  {

    init_file(file_name, image_width, image_height);

    auto file = std::fstream();
    file.open(file_name);
    if (!file.is_open())
    {
      std::cerr << "Failed to open file";
      return;
    }

    for (int row = image_height - 1; row >= 0; row--)
    {
      std::cerr << "\rScanline remaining: " << row << ' ' << std::flush;
      for (int col = 0; col < image_width; col++)
      {
        Color pixel_color = anti_alias(row, col);

        // gamma correction for gamma=2.0
        pixel_color =
            Color(std::sqrt(pixel_color.r()), std::sqrt(pixel_color.g()),
                  std::sqrt(pixel_color.b()));

        int line_to_write_to = 3 + col + 1 + (image_height - (row + 1)) * image_width;
        write_pixel_to_file(file, pixel_color, line_to_write_to);
      }
    }
    file.close();
  }

  void render_pixel_to_file(std::fstream &file, int row, int col)
  {

    Color pixel_color = anti_alias(row, col);

    pixel_color =
        Color(std::sqrt(pixel_color.r()), std::sqrt(pixel_color.g()),
              std::sqrt(pixel_color.b()));

    int line_to_write_to = 3 + col + 1 + (image_height - (row + 1)) * image_width;
    mtx.lock();
    write_pixel_to_file(file, pixel_color, line_to_write_to);
    mtx.unlock();
  }

  void render_to_file_threadded(const char *file_name)
  {

    init_file(file_name, image_width, image_height);

    auto file = std::fstream();
    file.open(file_name);
    if (!file.is_open())
    {
      std::cerr << "Failed to open file";
      return;
    }

    std::vector<std::thread> threads;
    for (int row = image_height - 1; row >= 0; row--)
    {
      std::cerr << "\rScanline remaining: " << row << ' ' << std::flush;
      for (int col = 0; col < image_width; col++)
      {
        threads.emplace_back(
            std::thread(&Render::render_pixel_to_file, this, std::ref(file), row, col));
      }
    }
    for (int row = image_height - 1; row >= 0; row--)
    {
      for (int col = 0; col < image_width; col++)
      {
        threads.back().join();
        threads.pop_back();
      }
      std::cerr << "\rThreadlines remaining: " << row << ' ' << std::flush;
    }
    file.close();
  }
};
