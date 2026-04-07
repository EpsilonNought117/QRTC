#include "qrtc.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "camera.hpp"


int main(void) 
{
    hittable_list world;

    world.add(sphere(point3(0.0f, 0.0f, -1.0f), 0.5f));
    world.add(sphere(point3(0.0f, -100.5f, -1.0f), 100.0f));
    camera cam;

    cam.aspect_ratio = 16.0 / 10.0;
    cam.image_width  = 2560;
    // cam.samples_per_pixel = 128;

    cam.render(world);
    return 0;
}