#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.hpp"
#include "sphere.hpp"

// Hit record
struct hit_record
{
    point3 p;
    vec3 normal;
    float t;
};

// Enum for type tagging
enum hittable_type
{
    HITTABLE_SPHERE = 0,
    HITTABLE_CUBE = 1
};

// Concrete object: sphere
struct sphere
{
    point3 center;
    float radius;
};

// Tagged union
struct hittable
{
    hittable_type type;

    union
    {
        sphere sph;
        // add more types later
    };
};

inline bool hit(
    const hittable& obj,
    const ray& r,
    float tmin,
    float tmax,
    hit_record& rec
)
{
    switch (obj.type)
    {
        case HITTABLE_SPHERE:
            return hit_sphere(obj.sph, r, tmin, tmax, rec);

        default:
            return false;
    }
}

#endif