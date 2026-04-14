#ifndef QRTC_VEC3_HPP
#define QRTC_VEC3_HPP

#include "qrtc_internal.hpp"

/**
 * Internal API Namespace
 */
namespace qrtc_internal
{

struct vec3f
{
    float x, y, z;

    vec3f() : x{0.0f}, y{0.0f}, z{0.0f} {}
    vec3f(float __x, float __y, float __z) : x{__x}, y{__y}, z{__z} {}
    vec3f(const vec3f& v1) { *this = v1; }

};

}

#endif // QRTC_VEC3_HPP