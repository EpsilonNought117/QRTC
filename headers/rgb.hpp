#ifndef QRTC_RGB_HPP
#define QRTC_RGB_HPP

#include "qrtc_internal.hpp"

namespace qrtc_internal
{

struct RGB
{
    float r = 0.0f, g = 0.0f, b = 0.0f;

    RGB() = default;
    RGB(float __r, float __g, float __b) : r{__r}, g{__g}, b{__b} {}

    RGB operator + () const { return *this; }
    RGB operator - () const { return RGB(-r, -g, -b); }

    inline RGB& operator += (const RGB& c1) { r += c1.r; g += c1.g; b += c1.b; return *this; }
    inline RGB& operator -= (const RGB& c1) { r -= c1.r; g -= c1.g; b -= c1.b; return *this; }
    inline RGB& operator *= (const RGB& c1) { r *= c1.r; g *= c1.g; b *= c1.b; return *this; }
    inline RGB& operator /= (const RGB& c1) { r /= c1.r; g /= c1.g; b /= c1.b; return *this; }
    inline RGB& operator *= (float f)       { r *= f;    g *= f;    b *= f;    return *this; }
    inline RGB& operator /= (float f)       { float inv = 1.0f / f; r *= inv; g *= inv; b *= inv; return *this; }

    inline void clamp()
    {
        r = r < 0.0f ? 0.0f : (r > 1.0f ? 1.0f : r);
        g = g < 0.0f ? 0.0f : (g > 1.0f ? 1.0f : g);
        b = b < 0.0f ? 0.0f : (b > 1.0f ? 1.0f : b);
    }
};

inline std::ostream& operator << (std::ostream& out, const RGB& c1)
{
    out << c1.r << ' ' << c1.g << ' ' << c1.b;
    return out;
}

inline RGB operator + (RGB c1, const RGB& c2) { return c1 += c2; }
inline RGB operator - (RGB c1, const RGB& c2) { return c1 -= c2; }
inline RGB operator * (RGB c1, const RGB& c2) { return c1 *= c2; }
inline RGB operator / (RGB c1, const RGB& c2) { return c1 /= c2; }
inline RGB operator * (RGB c1, float f)        { return c1 *= f; }
inline RGB operator * (float f, const RGB& c1) { return c1 *  f; }
inline RGB operator / (RGB c1, float f)        { return c1 /= f; }

}

#endif // QRTC_RGB_HPP