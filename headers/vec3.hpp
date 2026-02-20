#ifndef QRTC_VEC3_HPP
#define QRTC_VEC3_HPP

#include <cmath>
#include <iostream>

class vec3
{
public:
    float x, y, z;

    // Constructors
    vec3();
    vec3(float a, float b, float c);

    // Unary minus
    vec3 operator-() const;

    // Compound operators
    vec3& operator+=(const vec3& v);
    vec3& operator*=(float t);
    vec3& operator/=(float t);

    // Length functions
    float length_squared() const;
    float length() const;
};

using point3 = vec3;

// Stream output
std::ostream& operator<<(std::ostream& out, const vec3& v);

// Arithmetic operators
vec3 operator+(const vec3& u, const vec3& v);
vec3 operator-(const vec3& u, const vec3& v);
vec3 operator*(const vec3& u, const vec3& v);
vec3 operator*(float t, const vec3& v);
vec3 operator*(const vec3& v, float t);
vec3 operator/(const vec3& v, float t);

// Vector ops
float dot(const vec3& u, const vec3& v);
vec3 cross(const vec3& u, const vec3& v);
vec3 unit_vector(const vec3& v);

#endif