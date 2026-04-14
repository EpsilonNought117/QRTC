#ifndef QRTC_HPP
#define QRTC_HPP

// C++ Standard Headers
#include <iostream>
#include <memory>
#include <fstream>
#include <thread>
#include <string>
#include <atomic>

// C Standard headers
#include <cstdint>
#include <cmath>

/****************************************************************************************************/
/**************************   COMPILER, OS and CPU-ISA SPECIFIC HEADERS   ***************************/
/****************************************************************************************************/

#if defined(_WIN32)

    #if defined(_MSC_VER)
    
        #if defined(_M_X64) || defined(_M_AMD64)
        
            #include <immintrin.h>
            #include <intrin.h>
            #define QRTC_X64
        
        #elif defined(_M_ARM64) || defined(_M_ARM64EC)
        
            // TODO
            #define QRTC_ARM64
        
        #else
            #error "Unsupported CPU ISA on Windows and MSVC (Clang-cl can be used too)!"
        #endif
    
    #else
        #error "Unknown Compiler on Windows!"
    #endif

    #if defined(QRTC_BUILD_SHARED_LIB)

        #define QRTC_API __declspec(dllexport)
    
    #elif defined(QRTC_SHARED)
    
        #define QRTC_API __declspec(dllimport)

    #else
        #define QRTC_API
    #endif

#elif defined(__linux__) || defined(__linux)   || \
      defined(__unix__)  || defined(__unix)    || \
      defined(__APPLE__) || defined(__MACH__)

    #if defined(__GNUC__) || defined(__clang__)
        
        #if defined(__x86_64__)  || defined(__amd64__)  || \
            defined(__x86_64)    || defined(__amd64)
        
            #include <cpuid.h>
            #include <immintrin.h>
            #define QRTC_X64
        
        #elif defined(__aarch64__) || defined(__arm64__)
        
            #include <arm_acle.h>
            #include <arm_neon.h>
            #define QRTC_ARM64
        
        #else
            #error "Unsupported CPU ISA on Linux/Unix/macOS and GCC/Clang!"
        #endif

    #else
        #error "Unknown Compiler on Linux/Unix/macOS!"
    #endif

    #if defined(QRTC_BUILD_SHARED_LIB)

        #define QRTC_API __attribute__((visibility("default")))
    
    #else
        #define QRTC_API
    #endif

#else
    #error "Unknown Platform!"
#endif

namespace qrtc
{
    
}

#endif // QRTC_HPP