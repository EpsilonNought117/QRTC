#ifndef QRTC_IMAGE_HPP
#define QRTC_IMAGE_HPP

#include "qrtc_internal.hpp"
#include "rgb.hpp"

namespace qrtc_internal
{

struct Image
{
    std::size_t nx = 0;
    std::size_t ny = 0;
    std::shared_ptr<RGB[]> data = nullptr;

    Image() = default;
    Image(std::size_t width, std::size_t height);
    Image(std::size_t width, std::size_t height, const RGB& background);

    bool set(std::size_t x_coord, std::size_t y_coord, const RGB& color);
    void gamma_correct(float gamma);

    void write_ppm(std::ostream& out, bool is_P6);
    void read_ppm(std::string file_name);

    ~Image()
    {
        nx = 0;
        ny = 0;
        // don't have to do anything for the data
        // field as it's a std::unique_ptr
    }
};

}

#endif