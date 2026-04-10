#ifndef TORPEDORAY_HPP
#define TORPEDORAY_HPP

#if defined(_WIN32)

    #if defined(TR_BUILD_SHARED_LIB)

        #define TR_API __declspec(dllexport)
    
    #elif defined(TR_SHARED)
    
        #define TR_API __declspec(dllimport)

    #else
        #define TR_API
    #endif

#elif defined(__linux__) || defined(__linux)   || \
      defined(__unix__)  || defined(__unix)    || \
      defined(__APPLE__) || defined(__MACH__)

    #if defined(TR_BUILD_SHARED_LIB)
    
        #define TR_API __attribute__((visibility("default")))
    
    #else
        #define TR_API
    #endif

#else
    #error "Unknown OS!"
#endif

/**
 * Public API Namespace
 */
namespace TorpedoRay
{
    
}

#endif // TORPEDORAY_HPP