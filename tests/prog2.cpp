#include "../headers/ray.hpp"
#include "../headers/vec3.hpp"
#include "../headers/color.hpp"
#include <iostream>

float hit_sphere(const point3& center, float radius, const ray& r)
{
    vec3 oc = center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = h*h - a*c;

    if (discriminant < 0)
    {
        return -1.0f;
    }
    else 
    {
        return (h - std::sqrtf(discriminant)) / a;
    }
}

color ray_color(const ray& r)
{
    auto t = hit_sphere(point3(0,0,-1), 0.5, r);
    if (t > 0.0)
    {
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));    
        return 0.5*color(N.x + 1.0f, N.y + 1.0f, N.z + 1.0f);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y + 1.0);
    
    return (1.0f - a) * color(1.0f, 1.0f, 1.0f) + a * color(0.5f, 0.7f, 1.0f);
} 

int main(void)
{
    float focal_length = 1.0f;
    float aspect_ratio = 16.0f / 10.0f; // heigh / width
    int image_width = 1024;
    int image_height = int(image_width / aspect_ratio);
    image_height = image_height < 1 ? 1 : image_height;

    float viewport_height = 2.0;
    float viewport_width = viewport_height * (float(image_width) / image_height);
    auto camera_center = point3(0.0f, 0.0f, 0.0f);

    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++)
    {
        std::clog << "Scanlines remaining: " << (image_height - j) << " ... ";
        
        for (int i = 0; i < image_width; i++)
        {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            
            ray_direction = unit_vector(ray_direction);

            ray r(camera_center, ray_direction);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }

        std::clog << "Done!" << std::endl;
    }

    return 0;
}
