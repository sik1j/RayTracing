#ifndef COLOR_H
#define COLOR_H

#include "Vec3.h"
#include <iostream>

void write_color(std::ostream &os, Color pixel_color) {
    // Write the color value of each component mapped from [0,1] to [0,255]
    os << (int)(pixel_color.r() * 255) << ' '
       << (int)(pixel_color.g() * 255) << ' '
       << (int)(pixel_color.b() * 255) << '\n';
}


#endif