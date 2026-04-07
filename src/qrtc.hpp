#ifndef QRTC_HPP
#define QRTC_HPP

#include <cmath>
#include <iostream>
#include <limits>
#include <cstdlib>

// Constants
constexpr float infinity = std::numeric_limits<float>::infinity();
constexpr float pi       = 3.1415926535897932385f;

// Utility functions
inline float degrees_to_radians(float degrees)
{
    return degrees * pi / 180.0;
}

inline float random_float(void)
{
    return std::rand() / (RAND_MAX + 1.0f);
}

inline float random_float(float min, float max)
{
    return min + (max - min) * random_float();
}

// Common headers
#include "color.hpp"
#include "ray.hpp"
#include "vec3.hpp"

#endif