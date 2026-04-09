#ifndef COCOBEAN_HPP
#define COCOBEAN_HPP

#if defined(_WIN32)

    #if defined(CB_BUILD_SHARED_LIB)

        #define CB_API __declspec(dllexport)
    
    #elif defined(QRTC_SHARED)
    
        #define CB_API __declspec(dllimport)

    #else
        #define CB_API
    #endif

#elif defined(__linux__) || defined(__linux)   || \
      defined(__unix__)  || defined(__unix)    || \
      defined(__APPLE__) || defined(__MACH__)

    #if defined(QRTC_BUILD_SHARED_LIB)
    
        #define CB_API __attribute__((visibility("default")))
    
    #else
        #define CB_API
    #endif

#else
    #error "Unknown OS!"
#endif

/**
 * Public API Namespace
 */
namespace CocoBean
{

    

}

#endif // COCOBEAN_HPP