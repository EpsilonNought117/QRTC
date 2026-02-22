#ifndef QRTC_VEC3_HPP
#define QRTC_VEC3_HPP

#include <math.h>
#include <stdio.h>

typedef struct
{
    float x, y, z;

} vec3;

typedef vec3 point3;

/*
    out.x = v1.x + v2.x
    out.y = v1.y + v2.y
    out.z = v1.z + v2.z
*/
vec3 vec3Add(
    const vec3* v1, 
    const vec3* v2
);

/*
    out.x = v1.x - v2.x
    out.y = v1.y - v2.y
    out.z = v1.z - v2.z
*/
vec3 vec3Sub(
    const vec3* v1, 
    const vec3* v2
);

/*
    out.x = v1.x * v2.x
    out.y = v1.y * v2.y
    out.z = v1.z * v2.z
*/
vec3 vec3Prod(
    const vec3* v1, 
    const vec3* v2
);

/*
    out = v1 (cross) v2
*/
vec3 vec3CrossProd(
    const vec3* v1, 
    const vec3* v2
);

/*
    out.x = v1.x * t
    out.y = v1.y * t
    out.z = v1.z * t
*/
vec3 vec3ScaleVec(
    const vec3* v1, 
    float t
);

/*
    out = v1 / v1.length()
*/
vec3 vec3UnitVector(
    const vec3* v1
);

/*
    out = v1 (dot) v2
*/
float vec3DotProd(
    const vec3* v1, 
    const vec3* v2
);

/*
    out = v1.length() * v1.length()
*/
float vec3LengthSquared(
    const vec3* v1
);

/*
    out = v1.length()
*/
float vec3Length(
    const vec3* v1
);

/*
    Print vector elements to
    given file stream in order (x, y, z)
*/
void vec3PrintToFile(
    FILE* fp, 
    const vec3* v1
);

#endif