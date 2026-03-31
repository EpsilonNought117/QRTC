#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.hpp"
#include "vec3.hpp"
#include <cmath>

struct sphere
{
    point3 center;
    float radius;
};

// Intersection (no virtual dispatch)
inline bool hit_sphere(
    const sphere& s,
    const ray& r,
    float ray_tmin,
    float ray_tmax,
    hit_record& rec
)
{
    vec3 oc = s.center - r.orig;

    float a = r.dir.length_squared();
    float h = dot(r.dir, oc);
    float c = oc.length_squared() - s.radius * s.radius;

    float discriminant = h * h - a * c;

    if (discriminant < 0.0f)
    {
        return false;
    }

    float sqrtd = std::sqrt(discriminant);

    // Find nearest valid root
    float root = (h - sqrtd) / a;

    if (root <= ray_tmin || ray_tmax <= root)
    {
        root = (h + sqrtd) / a;

        if (root <= ray_tmin || ray_tmax <= root)
        {
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(root);
    rec.normal = (rec.p - s.center) / s.radius;

    return true;
}

#endif