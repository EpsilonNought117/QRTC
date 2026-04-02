#ifndef QRTC_HPP
#define QRTC_HPP

#include <cmath>
#include <iostream>
#include <limits>

// Constants
constexpr float infinity = std::numeric_limits<float>::infinity();
constexpr float pi       = 3.1415926535897932385f;

// Utility functions
inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

// Common headers
#include "color.hpp"
#include "ray.hpp"
#include "vec3.hpp"

#endif