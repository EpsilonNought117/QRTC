#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include "hittable.hpp"
#include "hit_record.hpp"
#include "qrtc.hpp"
#include "interval.hpp"
#include <vector>

struct hittable_list
{
    std::vector<hittable> objects;

    hittable_list () {}
    void clear(void) { objects.clear(); }
    void add(hittable obj) { objects.push_back(obj); }

    bool hit(
        const ray& r, 
        interval ray_t,
        hit_record& rec
    ) const
    {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        auto obj_list_size = objects.size();

        for (size_t i = 0; i < obj_list_size; i++)
        {
            if (objects[i].hit(r, interval(ray_t.min, closest_so_far), temp_rec))
            {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }    
};

#endif