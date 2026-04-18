#ifndef QRTC_ONB_HPP
#define QRTC_ONB_HPP

#include "qrtc_internal.hpp"
#include "vec3.hpp"

namespace qrtc_internal
{

struct ONB
{
    Vec3 u{}, v{}, w{};

    // ---------------- Constructors ----------------

    ONB() = default;

    ONB(const Vec3& a, const Vec3& b, const Vec3& c)
    {
        u = a; v = b; w = c;
    }

    // ---------------- Set ----------------

    inline void set(const Vec3& a, const Vec3& b, const Vec3& c)
    {
        u = a; v = b; w = c;
    }

    // ---------------- Init from single vector ----------------

    inline void init_from_w(const Vec3& n)
    {
        w = unit_vector(n);

        Vec3 a = (std::fabs(w.x()) > 0.9f)
               ? Vec3(0.0f, 1.0f, 0.0f)
               : Vec3(1.0f, 0.0f, 0.0f);

        v = unit_vector(cross(w, a));
        u = cross(w, v);
    }

    inline void init_from_u(const Vec3& n)
    {
        u = unit_vector(n);

        Vec3 a = (std::fabs(u.x()) > 0.9f)
               ? Vec3(0.0f, 1.0f, 0.0f)
               : Vec3(1.0f, 0.0f, 0.0f);

        w = unit_vector(cross(u, a));
        v = cross(w, u);
    }

    inline void init_from_v(const Vec3& n)
    {
        v = unit_vector(n);

        Vec3 a = (std::fabs(v.x()) > 0.9f)
               ? Vec3(0.0f, 1.0f, 0.0f)
               : Vec3(1.0f, 0.0f, 0.0f);

        u = unit_vector(cross(v, a));
        w = cross(u, v);
    }

    // ---------------- Init from two vectors ----------------

    inline void init_from_uv(const Vec3& _u, const Vec3& _v)
    {
        u = unit_vector(_u);
        w = unit_vector(cross(u, _v));
        v = cross(w, u);
    }

    inline void init_from_vu(const Vec3& _v, const Vec3& _u)
    {
        v = unit_vector(_v);
        w = unit_vector(cross(_u, v));
        u = cross(v, w);
    }

    inline void init_from_uw(const Vec3& _u, const Vec3& _w)
    {
        u = unit_vector(_u);
        v = unit_vector(cross(_w, u));
        w = cross(u, v);
    }

    inline void init_from_wu(const Vec3& _w, const Vec3& _u)
    {
        w = unit_vector(_w);
        v = unit_vector(cross(w, _u));
        u = cross(v, w);
    }

    inline void init_from_vw(const Vec3& _v, const Vec3& _w)
    {
        v = unit_vector(_v);
        u = unit_vector(cross(v, _w));
        w = cross(u, v);
    }

    inline void init_from_wv(const Vec3& _w, const Vec3& _v)
    {
        w = unit_vector(_w);
        u = unit_vector(cross(_v, w));
        v = cross(w, u);
    }
};

// ---------------- Comparison ----------------

inline bool operator == (const ONB& a, const ONB& b)
{
    return a.u == b.u &&
           a.v == b.v &&
           a.w == b.w;
}

// ---------------- Stream Ops ----------------

inline std::ostream& operator << (std::ostream& os, const ONB& onb)
{
    os << onb.u << '\n'
       << onb.v << '\n'
       << onb.w;
    return os;
}

inline std::istream& operator >> (std::istream& is, ONB& onb)
{
    is >> onb.u >> onb.v >> onb.w;
    return is;
}

} // namespace qrtc_internal

#endif // QRTC_ONB_HPP