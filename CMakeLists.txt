#   O---------------------------------------------------------------------------O
#   |                                                                           |
#   |                       TORPEDORAY CMAKE BUILD FILE                         |
#   |                                                                           |
#   O---------------------------------------------------------------------------O

cmake_minimum_required(VERSION 3.20)

project(TorpedoRay)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT (CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|AMD64|aarch64|ARM64)$"))
    message(FATAL_ERROR "Only x86-64 and ARM64 CPU ISAs are supported. Detected: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

# --- PLATFORM / COMPILER -------------------------------------------------------

if (WIN32)

    message(STATUS "Building TorpedoRay on 64-bit Windows")

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

    message(STATUS "Building TorpedoRay on macOS")

    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        message(STATUS "Compiler: Clang (version ${CMAKE_CXX_COMPILER_VERSION})")
    else ()
        message(FATAL_ERROR "Unsupported compiler on macOS: ${CMAKE_CXX_COMPILER_ID}")
    endif()

elseif (UNIX)

    message(STATUS "Building TorpedoRay on Unix/Linux")

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

option(TR_BUILD_SHARED_LIB "Build TorpedoRay as a shared library" OFF)
option(TR_BUILD_EXAMPLES   "Build usage example programs"         OFF)

option(TR_USE_FLOAT64 "Use double precision floating point instead of float32" OFF)

if (TR_USE_FLOAT64)
    message(STATUS "Precision: float64 (double)")
    add_compile_definitions(TR_F64)
else()
    message(STATUS "Precision: float32 (single)")
endif()

# --- ISA FLAGS -----------------------------------------------------------------

if (CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|AMD64)$")

    option(TR_AMD64_AVX     "Enable AVX code paths"      OFF)
    option(TR_AMD64_AVX512F "Enable AVX-512F code paths" OFF)
    option(TR_AMD64_DYNAMIC_DISPATCH "Runtime CPU dispatch" OFF)

    if (TR_AMD64_DYNAMIC_DISPATCH)

        if (TR_AMD64_AVX OR TR_AMD64_AVX512F)
            message(FATAL_ERROR
                "TR_AMD64_DYNAMIC_DISPATCH is ON — do not set TR_AMD64_AVX or TR_AMD64_AVX512F manually.")
        endif()

        message(STATUS "x86-64: Dynamic dispatch (SSE2 + AVX + AVX-512F)")
        add_compile_definitions(TR_AMD64_DYNAMIC_DISPATCH)

    else()

        if (TR_AMD64_AVX AND TR_AMD64_AVX512F)
            message(FATAL_ERROR "Only one of TR_AMD64_AVX / TR_AMD64_AVX512F may be enabled.")
        endif()

        if (TR_AMD64_AVX512F)
            message(STATUS "x86-64: AVX-512F enabled")
            add_compile_definitions(TR_AMD64_SSE2 TR_AMD64_AVX512F)

        elseif (TR_AMD64_AVX)
            message(STATUS "x86-64: AVX enabled")
            add_compile_definitions(TR_AMD64_SSE2 TR_AMD64_AVX)

        else()
            message(STATUS "x86-64: SSE2 baseline")
            add_compile_definitions(TR_AMD64_SSE2)
        endif()

    endif()

elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "^(aarch64|ARM64)$")

    option(TR_ARM64_DYNAMIC_DISPATCH "Runtime ARM64 dispatch" OFF)

    message(FATAL_ERROR "ARM64 path not implemented yet")

endif()

# --- SOURCES -------------------------------------------------------------------

set(TR_INTERNAL_SRC
)

set(TR_INTERNAL_HEADERS
    headers/vec3.hpp
    headers/TorpedoRayInternal.hpp
)

set(TR_SOURCES
    ${TR_INTERNAL_SRC}
    ${TR_INTERNAL_HEADERS}
)

# --- LIBRARY -------------------------------------------------------------------

if(TR_BUILD_SHARED_LIB)
    add_library(TR SHARED ${TR_SOURCES})
    message(STATUS "Building TorpedoRay as SHARED library")
    target_compile_definitions(TR PRIVATE TR_BUILD_SHARED_LIB)
else()
    add_library(TR STATIC ${TR_SOURCES})
    message(STATUS "Building TorpedoRay as STATIC library")
endif()

set(TR_TARGET TR)

# --- CONFIG DEFINES ------------------------------------------------------------

target_compile_definitions(${TR_TARGET} PRIVATE
    $<$<OR:$<CONFIG:Release>,$<CONFIG:MinSizeRel>>:TR_DISABLE_ASSERT>
)

# --- FILE PATH STRIPPING -------------------------------------------------------

if (MSVC AND NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${TR_TARGET} PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:/d1trimfile:${CMAKE_SOURCE_DIR}/>
    )

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND MSVC)
    target_compile_options(${TR_TARGET} PRIVATE
        /clang:-ffile-prefix-map=${CMAKE_SOURCE_DIR}/=
    )

else()
    target_compile_options(${TR_TARGET} PRIVATE
        -ffile-prefix-map=${CMAKE_SOURCE_DIR}/=
    )
endif()

# --- INCLUDES ------------------------------------------------------------------

target_include_directories(${TR_TARGET} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# --- OUTPUT --------------------------------------------------------------------

set_target_properties(${TR_TARGET} PROPERTIES
    OUTPUT_NAME "tpdr"
)