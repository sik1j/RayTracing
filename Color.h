#ifndef COLOR_H
#define COLOR_H

#include "Vec3.h"
#include <fstream>
#include <iomanip>
#include <iostream>

void write_color(std::ostream &os, Color pixel_color) {
    // Write the color value of each component mapped from [0,1] to [0,255]
    os << (int)(pixel_color.r() * 255) << ' '
       << (int)(pixel_color.g() * 255) << ' '
       << (int)(pixel_color.b() * 255) << '\n';
}

void init_file(const char* file_to_write, int image_width, int image_height) {
    auto file = std::ofstream();
    file.open(file_to_write);
    if(!file.is_open()) {
        std::cerr << "Failed to open file";
        return;
    }


    file 
        << "P3         \n" 
        << "400 225    \n" 
        << "255        \n";

    const int pixel_count = image_width*image_height;

    for (int i=0; i < pixel_count; i++) {
        file << "000 000 000\n";
    }
    file.close();
}

// @param file_row the row to put pixel_color in. Directly inserts into the given row regardless of the amount of header size
void write_pixel_to_file(std::fstream &file_to_write, Color pixel_color, int line_to_write_to) {
    // line_to_write_to - 1 because file lines are 1 indexed
    // LINE_CHAR_COUNT + 1 because file char pos is 0 indexed
    const int LINE_CHAR_COUNT = 12; 
    int char_pos_in_file = (LINE_CHAR_COUNT+1)*(line_to_write_to-1);
    file_to_write.seekp(char_pos_in_file);

    file_to_write << std::setfill('0') << std::setw(3)
         << (int)(pixel_color.r() * 255) << ' '
         << std::setfill('0') << std::setw(3)
         << (int)(pixel_color.g() * 255) << ' '
         << std::setfill('0') << std::setw(3)
         << (int)(pixel_color.b() * 255);
}


#endif
