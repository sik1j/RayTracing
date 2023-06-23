#include <iostream>

int main() {
    // Image Dimensions

    const int image_width = 256;
    const int image_height = 256;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // green decreases as row's increase
    for (int row = image_height-1; row >= 0; row--) {
        // red increases as col's increase
        for (int col = 0; col < image_width; col++) {
            // division maps: [0, image_height-1] -> [0, 1]
            double red = (double)row/(image_height - 1); 
            double green = (double)col/(image_width - 1);
            double blue = 0.25;

            int ired = (int)(red*255);
            int igreen = (int)(green*255);
            int iblue = (int)(blue*255);

            std::cout << ired << ' ' << igreen << ' ' << iblue << '\n';
        }
    }
}