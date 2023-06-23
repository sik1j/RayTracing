#include <iostream>
#include "Color.h"
#include "Vec3.h"

int main() {
    // Image Dimensions

    const int image_width = 256;
    const int image_height = 256;

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