#ifndef QRTC_IMAGE_HPP
#define QRTC_IMAGE_HPP

#include "qrtc_internal.hpp"
#include "rgb.hpp"

namespace qrtc_internal
{

struct image
{
    unsigned int nx = 0U;
    unsigned int ny = 0U;
    std::shared_ptr<rgb3f[]> data = nullptr;

    image() = default;
    image(unsigned int width, unsigned int height);
    image(unsigned int width, unsigned int height, const rgb3f& background);

    bool set(unsigned int x, unsigned int y, const rgb3f& color);
    void gamma_correct(float gamma);

    
    void write_ppm(std::ostream& out);
    void read_ppm(std::string file_name);
};



}

#endif