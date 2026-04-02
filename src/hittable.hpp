#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "qrtc.hpp"
#include "hit_record.hpp"
#include "sphere.hpp"

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

    inline bool hit(
        const ray& r,
        float tmin,
        float tmax,
        hit_record& rec
    ) const
    {
        switch (type)
        {
            case HITTABLE_SPHERE:
                return s.hit(r, tmin, tmax, rec);

            default:
                return false;
        }
    }
};

#endif