#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "qrtc.hpp"
#include "hit_record.hpp"
#include "sphere.hpp"
#include "interval.hpp"

// Enum for type tagging
enum hittable_type
{
    HITTABLE_SPHERE = 0
};

// Tagged union
struct hittable
{
    hittable_type type;

    union
    {
        sphere s;
        // add more types later
    };

    // Constructors
    hittable(const sphere& sph) : type(HITTABLE_SPHERE), s(sph) {}

    // Destructor (important for unions with non-trivial types later)
    ~hittable() {}

    bool hit(
        const ray& r,
        interval ray_t,
        hit_record& rec
    ) const
    {
        switch (type)
        {
            case HITTABLE_SPHERE:
                return s.hit(r, ray_t, rec);

            default:
                return false;
        }
    }
};

#endif