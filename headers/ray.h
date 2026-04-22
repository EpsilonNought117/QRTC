#ifndef QRTC_RAY_H
#define QRTC_RAY_H

#include "../include/qrtc.h"
#include "vec3.h"

typedef struct Ray
{
    Point3 orig;
    Vec3 dir;

} Ray;


static inline Point3 EvalRayAt(const Ray* r, float t /* parameter */)
{
    Point3 p = MulVec3Scalar(&(r->dir), t);
    AddVec3Inplace(&p, &(r->orig));
    return p;
}

#endif