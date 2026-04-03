#include "qrtc.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "interval.hpp"
#include "hit_record.hpp"
#include <iostream>

inline color ray_color(const ray& r, const hittable_list& world)
{
    hit_record rec;

    if (world.hit(r, interval(0.0f, infinity), rec))
    {
        return 0.5 * (rec.normal + color(1,1,1));
    }

    vec3 unit_direction = unit_vector(r.dir);
    auto a = 0.5*(unit_direction.y + 1.0);
    return (1.0f - a) * color(1.0f, 1.0f, 1.0f) + a * color(0.5f, 0.7f, 1.0f);
}

int main()
{
    // Image
    float aspect_ratio = 16.0f / 10.0f;
    int image_width = 1280;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(float(image_width) / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    hittable_list world;

    world.add(sphere(point3(0.0f, 0.0f, -1.0f), 0.5f));
    world.add(sphere(point3(0.0f, -100.5f, -1.0f), 100.0f));

    // Camera
    float focal_length = 1.0f;
    float viewport_height = 2.0f;
    float viewport_width = viewport_height * (float(image_width) / float(image_height));

    point3 camera_center(0.0f, 0.0f, 0.0f);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u(viewport_width, 0.0f, 0.0f);
    vec3 viewport_v(0.0f, -viewport_height, 0.0f);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    vec3 pixel_delta_u = viewport_u / float(image_width);
    vec3 pixel_delta_v = viewport_v / float(image_height);

    // Calculate the location of the upper left pixel.
    point3 viewport_upper_left =
        camera_center
        - vec3(0.0f, 0.0f, focal_length)
        - viewport_u * 0.5f
        - viewport_v * 0.5f;

    point3 pixel00_loc =
        viewport_upper_left + 0.5f * (pixel_delta_u + pixel_delta_v);

    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++)
    {
        std::clog << "Scanlines remaining: " << (image_height - j) << '\n';

        for (int i = 0; i < image_width; i++)
        {
            point3 pixel_center =
                pixel00_loc
                + float(i) * pixel_delta_u
                + float(j) * pixel_delta_v;

            vec3 ray_direction = pixel_center - camera_center;

            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r, world);

            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "Done.\n";
}