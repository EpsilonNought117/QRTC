#ifndef RAY_HPP
#define RAY_HPP

#include "qrtc.hpp"

struct ray
{
    point3 orig;
    vec3 dir;

    ray() {}

    ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

    point3 at(float t) const
    {
        return orig + t * dir;
    }
};

#endif