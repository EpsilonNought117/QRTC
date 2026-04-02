#ifndef HIT_RECORD_HPP
#define HIT_RECORD_HPP

#include "qrtc.hpp"

// Hit record
struct hit_record
{
    point3 p;
    vec3 normal;
    float t;
    bool front_face;

    hit_record () {}

    void set_face_normal(const ray& r, const vec3& outward_normal)
    {
        front_face = dot(r.dir, outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

#endif