#ifndef COLOR_HPP
#define COLOR_HPP

#include "vec3.hpp"
#include "interval.hpp"
#include <iostream>

using color = vec3;

inline void write_color(std::ostream& out, const color& pixel_color)
{
    auto r = pixel_color.x;
    auto g = pixel_color.y;
    auto b = pixel_color.z;

    static const interval intensity(0.0f, 256.0f);

    intensity.clamp(r);
    intensity.clamp(g);
    intensity.clamp(b);

    // Translate the [0,1] component values to the byte range [0,255] with rounding.
    int rbyte = int(255.0f * r + 0.5f);
    int gbyte = int(255.0f * g + 0.5f);
    int bbyte = int(255.0f * b + 0.5f);

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif