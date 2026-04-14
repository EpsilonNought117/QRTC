#ifndef QRTC_RGB_HPP
#define QRTC_RGB_HPP

#include "qrtc_internal.hpp"

namespace qrtc_internal
{

struct rgb3f
{
    float r = 0.0f, g = 0.0f, b = 0.0f;

    rgb3f() = default;
    rgb3f(float __r, float __g, float __b) : r{__r}, g{__g}, b{__b} {}

    rgb3f operator + () const { return *this; }
    rgb3f operator - () const { return rgb3f(-r, -g, -b); }

    inline rgb3f& operator += (const rgb3f& c1) { r += c1.r; g += c1.g; b += c1.b; return *this; }
    inline rgb3f& operator -= (const rgb3f& c1) { r -= c1.r; g -= c1.g; b -= c1.b; return *this; }
    inline rgb3f& operator *= (const rgb3f& c1) { r *= c1.r; g *= c1.g; b *= c1.b; return *this; }
    inline rgb3f& operator /= (const rgb3f& c1) { r /= c1.r; g /= c1.g; b /= c1.b; return *this; }
    inline rgb3f& operator *= (float f)         { r *= f;    g *= f;    b *= f;    return *this; }
    inline rgb3f& operator /= (float f)         { float inv = 1.0f / f; r *= inv; g *= inv; b *= inv; return *this; }

    inline void clamp()
    {
        r = r < 0.0f ? 0.0f : (r > 1.0f ? 1.0f : r);
        g = g < 0.0f ? 0.0f : (g > 1.0f ? 1.0f : g);
        b = b < 0.0f ? 0.0f : (b > 1.0f ? 1.0f : b);
    }
};

inline std::ostream& operator << (std::ostream& out, const rgb3f& c1)
{
    

    out << c1.r << ' ' << c1.g << ' ' << c1.b;
    return out;
}

inline rgb3f operator + (rgb3f c1, const rgb3f& c2) { return c1 += c2; }
inline rgb3f operator - (rgb3f c1, const rgb3f& c2) { return c1 -= c2; }
inline rgb3f operator * (rgb3f c1, const rgb3f& c2) { return c1 *= c2; }
inline rgb3f operator / (rgb3f c1, const rgb3f& c2) { return c1 /= c2; }
inline rgb3f operator * (rgb3f c1, float f)         { return c1 *= f;  }
inline rgb3f operator * (float f,  const rgb3f& c1) { return c1 *  f;  }
inline rgb3f operator / (rgb3f c1, float f)         { return c1 /= f;  }

}

#endif // QRTC_RGB_HPP