#include "../headers/qrtc_internal.hpp"
#include "../headers/Image.hpp"

namespace qrtc_internal
{

// ---------------- Constructors ----------------

Image::Image(std::size_t width, std::size_t height)
{
    if (width == 0 || height == 0)
    {
        std::cerr << "Error: Invalid image dimensions ("
                  << width << " x " << height << ")\n";
        std::exit(EXIT_FAILURE);
    }

    if (width > std::numeric_limits<std::size_t>::max() / height)
    {
        std::cerr << "Error: Image too large\n";
        std::exit(EXIT_FAILURE);
    }

    nx = width;
    ny = height;

    data = std::make_shared<RGB[]>(nx * ny);
}

Image::Image(std::size_t width, std::size_t height, const RGB& background)
    : Image(width, height)
{
    std::size_t img_size = nx * ny;
    for (std::size_t i = 0; i < img_size; i++)
        data[i] = background;
}

// ---------------- Pixel Set ----------------

bool Image::set(std::size_t x, std::size_t y, const RGB& color)
{
    if (!data)
    {
        std::cerr << "Error: Image not initialized\n";
        std::exit(EXIT_FAILURE);
    }

    if (x >= nx || y >= ny)
        return false;

    data[y * nx + x] = color;
    return true;
}

// ---------------- Gamma ----------------

void Image::gamma_correct(float gamma)
{
    float inv = 1.0f / gamma;
    std::size_t img_size = nx * ny;

    for (std::size_t i = 0; i < img_size; i++)
    {
        data[i].r = std::powf(data[i].r, inv);
        data[i].g = std::powf(data[i].g, inv);
        data[i].b = std::powf(data[i].b, inv);
    }
}

// ---------------- Write PPM ----------------

void Image::write_ppm(std::ostream& out, bool is_P6)
{
    const std::uint32_t maxval = 255;

    if (is_P6)
        out << "P6\n";
    else
        out << "P3\n";

    out << nx << ' ' << ny << '\n' << maxval << '\n';

    if (is_P6)
    {
        // --- binary ---
        for (std::size_t i = 0; i < nx * ny; i++)
        {
            RGB c = data[i];
            c.clamp();

            std::uint8_t r = std::uint8_t(255.0f * c.r + 0.5f);
            std::uint8_t g = std::uint8_t(255.0f * c.g + 0.5f);
            std::uint8_t b = std::uint8_t(255.0f * c.b + 0.5f);

            out.write(reinterpret_cast<char*>(&r), 1);
            out.write(reinterpret_cast<char*>(&g), 1);
            out.write(reinterpret_cast<char*>(&b), 1);
        }
    }
    else
    {
        // --- ASCII ---
        for (std::size_t i = 0; i < nx * ny; i++)
        {
            RGB c = data[i];
            c.clamp();

            std::uint16_t r = std::uint16_t(255.0f * c.r + 0.5f);
            std::uint16_t g = std::uint16_t(255.0f * c.g + 0.5f);
            std::uint16_t b = std::uint16_t(255.0f * c.b + 0.5f);

            out << r << ' ' << g << ' ' << b << '\n';
        }
    }
}

// ---------------- Read PPM ----------------

void Image::read_ppm(const std::string file_name)
{
    if (file_name.size() < 4 || file_name.substr(file_name.size() - 4) != ".ppm")
    {
        std::cerr << "Error: Invalid file extension: " << file_name << "\n";
        std::exit(EXIT_FAILURE);
    }

    std::ifstream in(file_name, std::ios::binary);
    if (!in)
    {
        std::cerr << "Error: Cannot open file: " << file_name << "\n";
        std::exit(EXIT_FAILURE);
    }

    std::string magic;
    in >> magic;

    if (magic != "P3" && magic != "P6")
    {
        std::cerr << "Error: Unsupported format: " << magic << "\n";
        std::exit(EXIT_FAILURE);
    }

    // --- skip comments ---
    auto skip_comments = [](std::istream& s)
    {
        while (true)
        {
            s >> std::ws;
            if (s.peek() == '#')
            {
                std::string tmp;
                std::getline(s, tmp);
            }
            else break;
        }
    };

    skip_comments(in);

    std::size_t cols, rows;
    in >> cols >> rows;

    skip_comments(in);

    std::uint32_t maxval;
    in >> maxval;

    if (!in || cols == 0 || rows == 0 || maxval == 0 || maxval > 65535)
    {
        std::cerr << "Error: Invalid header\n";
        std::exit(EXIT_FAILURE);
    }

    nx = cols;
    ny = rows;
    data = std::make_shared<RGB[]>(nx * ny);

    in.get(); // consume whitespace after maxval

    if (magic == "P3")
    {
        std::uint32_t r, g, b;

        for (std::size_t i = ny; i-- > 0;)
        {
            for (std::size_t j = 0; j < nx; j++)
            {
                skip_comments(in);

                if (!(in >> r >> g >> b))
                {
                    std::cerr << "Error: Corrupt P3 data\n";
                    std::exit(EXIT_FAILURE);
                }

                data[i * nx + j] = RGB(
                    float(r) / float(maxval),
                    float(g) / float(maxval),
                    float(b) / float(maxval)
                );
            }
        }
    }
    else // P6
    {
        const bool two_bytes = maxval > 255;

        for (std::size_t i = ny; i-- > 0;)
        {
            for (std::size_t j = 0; j < nx; j++)
            {
                std::uint32_t r, g, b;

                if (two_bytes)
                {
                    unsigned char buf[6];
                    if (!in.read(reinterpret_cast<char*>(buf), 6))
                    {
                        std::cerr << "Error: Corrupt P6 data\n";
                        std::exit(EXIT_FAILURE);
                    }

                    r = (buf[0] << 8) | buf[1];
                    g = (buf[2] << 8) | buf[3];
                    b = (buf[4] << 8) | buf[5];
                }
                else
                {
                    unsigned char buf[3];
                    if (!in.read(reinterpret_cast<char*>(buf), 3))
                    {
                        std::cerr << "Error: Corrupt P6 data\n";
                        std::exit(EXIT_FAILURE);
                    }

                    r = buf[0];
                    g = buf[1];
                    b = buf[2];
                }

                data[i * nx + j] = RGB(
                    float(r) / float(maxval),
                    float(g) / float(maxval),
                    float(b) / float(maxval)
                );
            }
        }
    }
}

} // namespace qrtc_internal