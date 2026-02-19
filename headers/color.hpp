#ifndef QRTC_COLOR_HPP
#define QRTC_COLOR_HPP

#include "vec3.hpp"

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color);

#endif