#   O---------------------------------------------------------------------------O
#   |                                                                           |
#   |                           QRTC CMAKE BUILD FILE                           |
#   |                                                                           |
#   O---------------------------------------------------------------------------O

# --- CHECKS --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)

project(QRTC)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT (CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|AMD64|aarch64|ARM64)$"))
    message(FATAL_ERROR "Only x86-64 and ARM64 CPU ISAs are supported. Detected: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

# Detect platform & compiler

if (WIN32)

    message(STATUS "Building on 64-bit Windows")

    if (MSVC)

        if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
            message(STATUS "Compiler: Clang-cl (version ${CMAKE_C_COMPILER_VERSION})")
        else ()
            message(STATUS "Compiler: MSVC (version ${MSVC_VERSION})")
        endif()

    else ()
        message(FATAL_ERROR "Unsupported compiler on Windows: ${CMAKE_C_COMPILER_ID}")
    endif()

elseif (APPLE)

    message(STATUS "Building on macOS")

    if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
        message(STATUS "Compiler: Clang (version ${CMAKE_C_COMPILER_VERSION})")
    else ()
        message(FATAL_ERROR "Unsupported compiler on macOS: ${CMAKE_C_COMPILER_ID}")
    endif()

elseif (UNIX)

    message(STATUS "Building on Unix/Linux")

    if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
        message(STATUS "Compiler: GCC (version ${CMAKE_C_COMPILER_VERSION})")
    elseif (CMAKE_C_COMPILER_ID STREQUAL "Clang")
        message(STATUS "Compiler: Clang (version ${CMAKE_C_COMPILER_VERSION})")
    else ()
        message(FATAL_ERROR "Unsupported compiler on Unix/Linux: ${CMAKE_C_COMPILER_ID}")
    endif()

else ()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

# --- BUILD OPTIONS -------------------------------------------------------------

option(QRTC_BUILD_SHARED_LIB  "Build QRTC as a shared library"  OFF)
option(QRTC_BUILD_EXAMPLES    "Build usage example programs"     OFF)

# Floating-point precision — defaults to float32 unless QRTC_USE_FLOAT64 is set
option(QRTC_USE_FLOAT64  "Use 64-bit (double) precision instead of the default 32-bit"  OFF)

if (QRTC_USE_FLOAT64)
    message(STATUS "Precision: float64 (double)")
    add_compile_definitions(QRTC_FLOAT64)
else()
    message(STATUS "Precision: float32 (single, default)")
    add_compile_definitions(QRTC_FLOAT32)
endif()

# --- ISA AND EXTENSION SPECIFIC FLAGS ------------------------------------------

if (CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|AMD64)$")
    # --- x86-64 / AMD64 --------------------------------------------------------

    option(QRTC_AMD64_SSE2             "Enable SSE2 code paths"                 OFF)
    option(QRTC_AMD64_AVX              "Enable AVX code paths"                  OFF)
    option(QRTC_AMD64_AVX512F          "Enable AVX-512F code paths"             OFF)
    option(QRTC_AMD64_DYNAMIC_DISPATCH "Build with runtime x86-64 CPU dispatch" OFF)

    # Count how many scalar ISA flags are explicitly enabled
    set(_QRTC_ISA_COUNT 0)

    if (QRTC_AMD64_SSE2)
        math(EXPR _QRTC_ISA_COUNT "${_QRTC_ISA_COUNT} + 1")
    endif()
    if (QRTC_AMD64_AVX)
        math(EXPR _QRTC_ISA_COUNT "${_QRTC_ISA_COUNT} + 1")
    endif()
    if (QRTC_AMD64_AVX512F)
        math(EXPR _QRTC_ISA_COUNT "${_QRTC_ISA_COUNT} + 1")
    endif()

    if (QRTC_AMD64_DYNAMIC_DISPATCH)

        if (_QRTC_ISA_COUNT GREATER 0)
            message(FATAL_ERROR
                "QRTC_AMD64_DYNAMIC_DISPATCH is ON — do not set QRTC_AMD64_SSE2, "
                "QRTC_AMD64_AVX, or QRTC_AMD64_AVX512F manually. "
                "Dynamic dispatch builds all three automatically.")
        endif()
    
        message(STATUS "x86-64: Dynamic dispatch enabled (SSE2 + AVX + AVX-512F)")
        add_compile_definitions(QRTC_AMD64_SSE2 QRTC_AMD64_AVX QRTC_AMD64_AVX512F QRTC_AMD64_DYNAMIC_DISPATCH)
    
    else()
    
        if (_QRTC_ISA_COUNT GREATER 1)
            message(FATAL_ERROR
                "Only one of QRTC_AMD64_SSE2 / QRTC_AMD64_AVX / QRTC_AMD64_AVX512F "
                "may be enabled at a time for a static build. "
                "To target all three, use -DQRTC_AMD64_DYNAMIC_DISPATCH=ON instead.")
        endif()

        if (QRTC_AMD64_SSE2)
            message(STATUS "x86-64: SSE2 code paths enabled")
            add_compile_definitions(QRTC_AMD64_SSE2)
        elseif (QRTC_AMD64_AVX)
            message(STATUS "x86-64: AVX code paths enabled")
            add_compile_definitions(QRTC_AMD64_AVX)
        elseif (QRTC_AMD64_AVX512F)
            message(STATUS "x86-64: AVX-512F code paths enabled")
            add_compile_definitions(QRTC_AMD64_AVX512F)
        else()
            message(STATUS "x86-64: No ISA extension selected — generic scalar build")
        endif()
    endif()

elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "^(aarch64|ARM64)$")
    # --- AArch64 / ARM64 -------------------------------------------------------

    option(QRTC_ARM64_DYNAMIC_DISPATCH "Build with runtime ARM64 CPU dispatch" OFF)

endif()