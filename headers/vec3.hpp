#ifndef QRTC_VEC3_HPP
#define QRTC_VEC3_HPP

#include "qrtc_internal.hpp"

/**
 * Internal API Namespace
 */
namespace qrtc_internal
{

struct Vec3
{
    float x = 0.0f, y = 0.0f, z = 0.0f;

    Vec3() = default;
    Vec3(float __x, float __y, float __z) : x{__x}, y{__y}, z{__z} {}
    Vec3(const Vec3& v) { *this = v; }

    inline Vec3 operator + () const { return *this;            }
    inline Vec3 operator - () const { return Vec3(-x, -y, -z); }

    inline float length_squared() const { return x * x + y * y + z * z;        }
    inline float length()         const { return std::sqrtf(length_squared()); }

    inline Vec3& operator = (const Vec3& v) { *this = v; }
};

} // namespace qrtc_internal

#endif // QRTC_VEC3_HPP