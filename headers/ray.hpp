#ifndef QRTC_RAY_HPP
#define QRTC_RAY_HPP

#include "vec3.hpp"

class ray
{
public:
    ray();
    ray(const point3& origin, const vec3& direction);

    const point3& origin() const;
    const vec3& direction() const;

    point3 at(float t) const;

private:
    point3 orig;
    vec3   dir;
};

#endif