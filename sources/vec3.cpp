#include "../headers/vec3.hpp"

// ================= Constructors =================

vec3::vec3()
    : x{0.0f}, y{0.0f}, z{0.0f}
{}

vec3::vec3(float a, float b, float c)
    : x{a}, y{b}, z{c}
{}

// ================= Member operators =================

vec3 vec3::operator-() const
{
    return vec3{-x, -y, -z};
}

vec3& vec3::operator+=(const vec3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

vec3& vec3::operator*=(float t)
{
    x *= t;
    y *= t;
    z *= t;
    return *this;
}

vec3& vec3::operator/=(float t)
{
    return (*this) *= (1.0f / t);
}

// ================= Length =================

float vec3::length_squared() const
{
    return x * x + y * y + z * z;
}

float vec3::length() const
{
    return std::sqrt(length_squared());
}

// ================= Free operators =================

std::ostream& operator<<(std::ostream& out, const vec3& v)
{
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

vec3 operator+(const vec3& u, const vec3& v)
{
    return vec3{u.x + v.x, u.y + v.y, u.z + v.z};
}

vec3 operator-(const vec3& u, const vec3& v)
{
    return vec3{u.x - v.x, u.y - v.y, u.z - v.z};
}

vec3 operator*(const vec3& u, const vec3& v)
{
    return vec3{u.x * v.x, u.y * v.y, u.z * v.z};
}

vec3 operator*(float t, const vec3& v)
{
    return vec3{t * v.x, t * v.y, t * v.z};
}

vec3 operator*(const vec3& v, float t)
{
    return t * v;
}

vec3 operator/(const vec3& v, float t)
{
    return (1.0f / t) * v;
}

// ================= Vector math =================

double dot(const vec3& u, const vec3& v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

vec3 cross(const vec3& u, const vec3& v)
{
    return vec3{
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    };
}

vec3 unit_vector(const vec3& v)
{
    return v / v.length();
}