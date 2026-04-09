#ifndef QRTC_VEC3_HPP
#define QRTC_VEC3_HPP

#include "../include/qrtc.hpp"

template <typename T>
struct vec3
{
    T x, y, z;


};

#if defined(QRTC_FLOAT32)

#if defined(QRTC_AMD64_SSE2) || defined(QRTC_AMD64_DYNAMIC_DISPATCH)



#endif

#elif defined(QRTC_FLOAT64)



#else
    #error "QRTC can only work with 64-bit or 32-bit floats!"
#endif



#endif