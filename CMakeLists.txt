#   O---------------------------------------------------------------------------O
#   |                                                                           |
#   |                         QRTC CMAKE BUILD FILE                              |
#   |                                                                           |
#   O---------------------------------------------------------------------------O

cmake_minimum_required(VERSION 3.20)

project(QRTC)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT (CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|AMD64|aarch64|ARM64)$"))
    message(FATAL_ERROR "Only x86-64 and ARM64 CPU ISAs are supported. Detected: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

# --- PLATFORM / COMPILER -------------------------------------------------------

if (WIN32)

    message(STATUS "Building QRTC on 64-bit Windows")

    if (MSVC)
        if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            message(STATUS "Compiler: Clang-cl (version ${CMAKE_CXX_COMPILER_VERSION})")
        else ()
            message(STATUS "Compiler: MSVC (version ${MSVC_VERSION})")
        endif()
    else ()
        message(FATAL_ERROR "Unsupported compiler on Windows: ${CMAKE_CXX_COMPILER_ID}")
    endif()

elseif (APPLE)

    message(STATUS "Building QRTC on macOS")

    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        message(STATUS "Compiler: Clang (version ${CMAKE_CXX_COMPILER_VERSION})")
    else ()
        message(FATAL_ERROR "Unsupported compiler on macOS: ${CMAKE_CXX_COMPILER_ID}")
    endif()

elseif (UNIX)

    message(STATUS "Building QRTC on Unix/Linux")

    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message(STATUS "Compiler: GCC (version ${CMAKE_CXX_COMPILER_VERSION})")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        message(STATUS "Compiler: Clang (version ${CMAKE_CXX_COMPILER_VERSION})")
    else ()
        message(FATAL_ERROR "Unsupported compiler on Unix/Linux: ${CMAKE_CXX_COMPILER_ID}")
    endif()

else ()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

# --- BUILD OPTIONS -------------------------------------------------------------

option(QRTC_BUILD_SHARED_LIB "Build QRTC as a shared library" OFF)
option(QRTC_BUILD_EXAMPLES   "Build usage example programs"   OFF)

# --- ISA FLAGS -----------------------------------------------------------------

if (CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|AMD64)$")

    option(QRTC_AMD64_AVX              "Enable AVX code paths"      OFF)
    option(QRTC_AMD64_AVX512F          "Enable AVX-512F code paths" OFF)
    option(QRTC_AMD64_DYNAMIC_DISPATCH "Runtime CPU dispatch"       OFF)

    if (QRTC_AMD64_DYNAMIC_DISPATCH)

        if (QRTC_AMD64_AVX OR QRTC_AMD64_AVX512F)
            message(FATAL_ERROR
                "QRTC_AMD64_DYNAMIC_DISPATCH is ON — do not set QRTC_AMD64_AVX or QRTC_AMD64_AVX512F manually.")
        endif()

        message(STATUS "x86-64: Dynamic dispatch (SSE2 + AVX + AVX-512F)")
        add_compile_definitions(QRTC_AMD64_DYNAMIC_DISPATCH)

    else()

        if (QRTC_AMD64_AVX AND QRTC_AMD64_AVX512F)
            message(FATAL_ERROR "Only one of QRTC_AMD64_AVX / QRTC_AMD64_AVX512F may be enabled.")
        endif()

        if (QRTC_AMD64_AVX512F)
            message(STATUS "x86-64: AVX-512F enabled")
            add_compile_definitions(QRTC_AMD64_SSE2 QRTC_AMD64_AVX512F)

        elseif (QRTC_AMD64_AVX)
            message(STATUS "x86-64: AVX enabled")
            add_compile_definitions(QRTC_AMD64_SSE2 QRTC_AMD64_AVX)

        else()
            message(STATUS "x86-64: SSE2 baseline")
            add_compile_definitions(QRTC_AMD64_SSE2)
        endif()

    endif()

elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "^(aarch64|ARM64)$")

    option(QRTC_ARM64_DYNAMIC_DISPATCH "Runtime ARM64 dispatch" OFF)

    message(FATAL_ERROR "ARM64 path not implemented yet")

endif()

# --- SOURCES -------------------------------------------------------------------

set(QRTC_INTERNAL_SRC

    src/image.cpp
)

set(QRTC_INTERNAL_HEADERS
    
    headers/onb.hpp
    headers/image.hpp
    headers/RGB.hpp
    headers/vec3.hpp
    headers/qrtc_internal.hpp
)

set(QRTC_SOURCES
    ${QRTC_INTERNAL_SRC}
    ${QRTC_INTERNAL_HEADERS}
)

# --- LIBRARY -------------------------------------------------------------------

if(QRTC_BUILD_SHARED_LIB)
    add_library(QRTC SHARED ${QRTC_SOURCES})
    message(STATUS "Building QRTC as SHARED library")
    target_compile_definitions(QRTC PRIVATE QRTC_BUILD_SHARED_LIB)
else()
    add_library(QRTC STATIC ${QRTC_SOURCES})
    message(STATUS "Building QRTC as STATIC library")
endif()

set(QRTC_TARGET QRTC)

# --- CONFIG DEFINES ------------------------------------------------------------

target_compile_definitions(${QRTC_TARGET} PRIVATE
    $<$<OR:$<CONFIG:Release>,$<CONFIG:MinSizeRel>>:QRTC_DISABLE_ASSERT>
)

# --- FILE PATH STRIPPING -------------------------------------------------------

if (MSVC AND NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${QRTC_TARGET} PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:/d1trimfile:${CMAKE_SOURCE_DIR}/>
    )

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND MSVC)
    target_compile_options(${QRTC_TARGET} PRIVATE
        /clang:-ffile-prefix-map=${CMAKE_SOURCE_DIR}/=
    )

else()
    target_compile_options(${QRTC_TARGET} PRIVATE
        -ffile-prefix-map=${CMAKE_SOURCE_DIR}/=
    )
endif()

# --- INCLUDES ------------------------------------------------------------------

target_include_directories(${QRTC_TARGET} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# --- OUTPUT --------------------------------------------------------------------

set_target_properties(${QRTC_TARGET} PROPERTIES
    OUTPUT_NAME "qrtc"
)