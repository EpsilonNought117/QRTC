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
    float e[3] = {0.0f, 0.0f, 0.0f};

    // ---------------- Constructors ----------------

    Vec3() = default;

    Vec3(float e0, float e1, float e2)
    {
        e[0] = e0; e[1] = e1; e[2] = e2;
    }

    Vec3(const Vec3& v) { *this = v; }

    // ---------------- Access ----------------

    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }

    inline float operator[](int i) const { return e[i]; }
    inline float& operator[](int i)      { return e[i]; }

    // ---------------- Unary ----------------

    inline Vec3 operator + () const { return *this; }

    inline Vec3 operator - () const
    {
        return Vec3(-e[0], -e[1], -e[2]);
    }

    // ---------------- Length ----------------

    inline float length_squared() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    inline float length() const
    {
        return std::sqrtf(length_squared());
    }

    inline void make_unit_vector()
    {
        float k = 1.0f / length();
        e[0] *= k; e[1] *= k; e[2] *= k;
    }

    // ---------------- Setters ----------------

    inline void set_x(float v) { e[0] = v; }
    inline void set_y(float v) { e[1] = v; }
    inline void set_z(float v) { e[2] = v; }

    // ---------------- Component Ops ----------------

    inline float min_component() const
    {
        return std::fmin(e[0], std::fmin(e[1], e[2]));
    }

    inline float max_component() const
    {
        return std::fmax(e[0], std::fmax(e[1], e[2]));
    }

    inline float max_abs_component() const
    {
        return std::fmax(std::fabs(e[0]),
               std::fmax(std::fabs(e[1]), std::fabs(e[2])));
    }

    inline float min_abs_component() const
    {
        return std::fmin(std::fabs(e[0]),
               std::fmin(std::fabs(e[1]), std::fabs(e[2])));
    }

    inline int index_of_min_component() const
    {
        return (e[0] < e[1] && e[0] < e[2]) ? 0 :
               (e[1] < e[2] ? 1 : 2);
    }

    inline int index_of_max_component() const
    {
        return (e[0] > e[1] && e[0] > e[2]) ? 0 :
               (e[1] > e[2] ? 1 : 2);
    }

    inline int index_of_min_abs_component() const
    {
        float ax = std::fabs(e[0]), ay = std::fabs(e[1]), az = std::fabs(e[2]);
        return (ax < ay && ax < az) ? 0 :
               (ay < az ? 1 : 2);
    }

    inline int index_of_max_abs_component() const
    {
        float ax = std::fabs(e[0]), ay = std::fabs(e[1]), az = std::fabs(e[2]);
        return (ax > ay && ax > az) ? 0 :
               (ay > az ? 1 : 2);
    }

    // ---------------- Assignment Ops ----------------

    inline Vec3& operator = (const Vec3& v)
    {
        e[0] = v.e[0];
        e[1] = v.e[1];
        e[2] = v.e[2];
        return *this;
    }

    inline Vec3& operator += (const Vec3& v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    inline Vec3& operator -= (const Vec3& v)
    {
        e[0] -= v.e[0];
        e[1] -= v.e[1];
        e[2] -= v.e[2];
        return *this;
    }

    inline Vec3& operator *= (float t)
    {
        e[0] *= t; e[1] *= t; e[2] *= t;
        return *this;
    }

    inline Vec3& operator /= (float t)
    {
        float inv = 1.0f / t;
        e[0] *= inv; e[1] *= inv; e[2] *= inv;
        return *this;
    }
};

// ---------------- Comparison ----------------

inline bool operator == (const Vec3& a, const Vec3& b)
{
    return a.e[0] == b.e[0] &&
           a.e[1] == b.e[1] &&
           a.e[2] == b.e[2];
}

inline bool operator != (const Vec3& a, const Vec3& b)
{
    return !(a == b);
}

// ---------------- Arithmetic ----------------

inline Vec3 operator + (const Vec3& a, const Vec3& b)
{
    return Vec3(a.e[0] + b.e[0],
                a.e[1] + b.e[1],
                a.e[2] + b.e[2]);
}

inline Vec3 operator - (const Vec3& a, const Vec3& b)
{
    return Vec3(a.e[0] - b.e[0],
                a.e[1] - b.e[1],
                a.e[2] - b.e[2]);
}

inline Vec3 operator * (const Vec3& a, const Vec3& b)
{
    return Vec3(a.e[0] * b.e[0],
                a.e[1] * b.e[1],
                a.e[2] * b.e[2]);
}

inline Vec3 operator * (const Vec3& v, float t)
{
    return Vec3(v.e[0] * t,
                v.e[1] * t,
                v.e[2] * t);
}

inline Vec3 operator * (float t, const Vec3& v)
{
    return v * t;
}

inline Vec3 operator / (const Vec3& v, float t)
{
    float inv = 1.0f / t;
    return Vec3(v.e[0] * inv,
                v.e[1] * inv,
                v.e[2] * inv);
}

// ---------------- Vector Ops ----------------

inline float dot(const Vec3& a, const Vec3& b)
{
    return a.e[0] * b.e[0] +
           a.e[1] * b.e[1] +
           a.e[2] * b.e[2];
}

inline Vec3 cross(const Vec3& a, const Vec3& b)
{
    return Vec3(
        a.e[1] * b.e[2] - a.e[2] * b.e[1],
        a.e[2] * b.e[0] - a.e[0] * b.e[2],
        a.e[0] * b.e[1] - a.e[1] * b.e[0]
    );
}

inline Vec3 unit_vector(const Vec3& v)
{
    return v / v.length();
}

inline Vec3 min_vec(const Vec3& a, const Vec3& b)
{
    return Vec3(
        std::fmin(a.e[0], b.e[0]),
        std::fmin(a.e[1], b.e[1]),
        std::fmin(a.e[2], b.e[2])
    );
}

inline Vec3 max_vec(const Vec3& a, const Vec3& b)
{
    return Vec3(
        std::fmax(a.e[0], b.e[0]),
        std::fmax(a.e[1], b.e[1]),
        std::fmax(a.e[2], b.e[2])
    );
}

inline float triple_product(const Vec3& a, const Vec3& b, const Vec3& c)
{
    return dot(a, cross(b, c));
}

// ---------------- Stream Ops ----------------

inline std::ostream& operator << (std::ostream& os, const Vec3& v)
{
    os << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
    return os;
}

inline std::istream& operator >> (std::istream& is, Vec3& v)
{
    is >> v.e[0] >> v.e[1] >> v.e[2];
    return is;
}

} // namespace qrtc_internal

#endif // QRTC_VEC3_HPP