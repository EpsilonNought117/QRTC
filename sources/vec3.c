#include "../headers/vec3.h"

vec3 vec3Add(
    const vec3 *v1,
    const vec3 *v2
)
{
    vec3 out;

    out.x = v1->x + v2->x;
    out.y = v1->y + v2->y;
    out.z = v1->z + v2->z;

    return out;
}

vec3 vec3Sub(
    const vec3 *v1,
    const vec3 *v2
)
{
    vec3 out;

    out.x = v1->x - v2->x;
    out.y = v1->y - v2->y;
    out.z = v1->z - v2->z;

    return out;
}

vec3 vec3Prod(
    const vec3 *v1,
    const vec3 *v2
)
{
    vec3 out;

    out.x = v1->x * v2->x;
    out.y = v1->y * v2->y;
    out.z = v1->z * v2->z;
    
    return out;
}

vec3 vec3CrossProd(
    const vec3* v1,
    const vec3* v2
)
{ 
    vec3 out;

    out.x = (v1->y * v2->z) - (v1->z * v2->y);
    out.y = (v1->z * v2->x) - (v1->x * v2->z);
    out.z = (v1->x * v2->y) - (v1->y * v2->x);

    return out;
}

vec3 vec3ScaleVec(
    const vec3* v1,
    float t
)
{
    vec3 out;

    out.x = v1->x * t;
    out.y = v1->y * t;
    out.z = v1->z * t;

    return out;
}

vec3 vec3UnitVector(
    const vec3* v1
)
{
    float t = vec3Length(v1);
    vec3 out = vec3ScaleVec(v1, 1 / t);
    return out;
}

float vec3DotProd(
    const vec3* v1,
    const vec3* v2
)
{
    return (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
}

float vec3LengthSquared(
    const vec3* v1
)
{
    return (v1->x * v1->x) + (v1->y * v1->y) + (v1->z * v1->z);
}

float vec3Length(
    const vec3* v1
)
{
    return sqrtf(vec3LengthSquared(v1));
}

void vec3PrintToFile(
    FILE* fp,
    const vec3* v1
)
{
    fprintf(fp, "%g %g %g", v1->x, v1->y, v1->z);
    return;
}

