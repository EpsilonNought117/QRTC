#ifndef SPHERE_H
#define SPHERE_H

#include "hit_record.hpp"
#include "qrtc.hpp"
#include "interval.hpp"
#include <cmath>

struct sphere
{
    point3 center;
    float radius;

    sphere(point3 c, float r) : center{c} , radius{r} {};

    inline bool hit(
        const ray& r,
        interval ray_t,
        hit_record& rec
    ) const
    {
        vec3 oc = center - r.orig;

        float a = r.dir.length_squared();
        float h = dot(r.dir, oc);
        float c = oc.length_squared() - radius * radius;

        float discriminant = h * h - a * c;

        if (discriminant < 0.0f)
        {
            return false;
        }

        float sqrtd = std::sqrt(discriminant);

        // Find nearest valid root
        float root = (h - sqrtd) / a;

        if (!ray_t.surrounds(root))
        {
            root = (h + sqrtd) / a;

            if (!ray_t.surrounds(root))
            {
                return false;
            }
        }

        rec.t = root;
        rec.p = r.at(root);

        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }
};

#endif