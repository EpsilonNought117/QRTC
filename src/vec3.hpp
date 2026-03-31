#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <iostream>

struct vec3
{
    float x, y, z;

    // Constructors
    vec3() : x(0.0f), y(0.0f), z(0.0f) { /* do nothing */ }
    vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) { /* do nothing */ }

    vec3 operator+() const
    {
        return vec3(x, y, z);
    }

    // Unary minus
    vec3 operator-() const
    {
        return vec3(-x, -y, -z);
    }

    // Compound operators
    vec3& operator+=(const vec3& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    vec3& operator*=(float t)
    {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    vec3& operator/=(float t)
    {
        return *this *= 1.0f / t;
    }

    // Length functions
    float length() const
    {
        return std::sqrt(length_squared());
    }

    float length_squared() const
    {
        return x * x + y * y + z * z;
    }
};

// Alias
using point3 = vec3;

// Utility functions

inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline vec3 operator+(const vec3& u, const vec3& v)
{
    return vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline vec3 operator-(const vec3& u, const vec3& v)
{
    return vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

// Hadamard (element-wise) product
inline vec3 operator*(const vec3& u, const vec3& v)
{
    return vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

// Scalar multiplication
inline vec3 operator*(float t, const vec3& v)
{
    return vec3(t * v.x, t * v.y, t * v.z);
}

inline vec3 operator*(const vec3& v, float t)
{
    return t * v;
}

inline vec3 operator/(const vec3& v, float t)
{
    return (1.0f / t) * v;
}

// Dot product
inline float dot(const vec3& u, const vec3& v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

// Cross product
inline vec3 cross(const vec3& u, const vec3& v)
{
    return vec3(
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    );
}

// Normalize
inline vec3 unit_vector(const vec3& v)
{
    return v / v.length();
}

#endif