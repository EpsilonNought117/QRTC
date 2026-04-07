#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "hittable_list.hpp"
#include "hittable.hpp"

struct camera
{
    float aspect_ratio      = 1.0f;  // Ratio of image width over height
    int   image_width       = 100;   // Rendered image width in pixel count
    int   samples_per_pixel = 16;

    float  pixel_samples_scale;
    int    image_height;   // Rendered image height
    point3 center;         // Camera center
    point3 pixel00_loc;    // Location of pixel 0, 0
    vec3   pixel_delta_u;  // Offset to pixel to the right
    vec3   pixel_delta_v;  // Offset to pixel below

    void initialize() 
    {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_samples_scale = 1.0f / samples_per_pixel;

        center = point3(0.0f, 0.0f, 0.0f);
        
        // Determine viewport dimensions.
        auto focal_length = 1.0f;
        auto viewport_height = 2.0f;
        auto viewport_width = viewport_height * (float(image_width) / image_height);
        
        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;
        
        // Calculate the location of the upper left pixel.
        auto viewport_upper_left = center - vec3(0.0f, 0.0f, focal_length) - viewport_u / 2.0f - viewport_v / 2.0f;
        
        pixel00_loc = viewport_upper_left + 0.5f * (pixel_delta_u + pixel_delta_v);
    }

    color ray_color(const ray& r, const hittable_list& world) const
    {
        hit_record rec;

        if (world.hit(r, interval(0.0f, infinity), rec))
        {
            return 0.5f * (rec.normal + color(1.0f, 1.0f, 1.0f));
        }

        vec3 unit_direction = unit_vector(r.dir);
        auto a = 0.5f * (unit_direction.y + 1.0f);

        return (1.0f - a) * color(1.0f, 1.0f, 1.0f) + a * color(0.5f, 0.7f, 1.0f);
    }
    
    void render(const hittable_list& world)
    {
        initialize();
    
        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++)
        {
            std::clog << "Scanline: " << (image_height - j) << " ... ";
        
            for (int i = 0; i < image_width; i++)
            {
                color pixel_color(0.0f, 0.0f, 0.0f);

                for (int sample = 0; sample < samples_per_pixel; sample++)
                {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, world);
                }

                write_color(std::cout, pixel_color * pixel_samples_scale);
            }
            
            std::clog << "Done.\n";
        }
    }

    ray get_ray(int i, int j) const 
    {
        auto offset = sample_square();
        auto pixel_sample = pixel00_loc 
                            + ((i + offset.x) * pixel_delta_u) 
                            + ((j + offset.y) * pixel_delta_v);

        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square(void) const
    {
        return vec3(random_float() - 0.5f, random_float() - 0.5f, 0.0f);
    }
};

#endif