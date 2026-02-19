#   O---------------------------------------------------------------------------O
#   |                                                                           |
#   |                          QRTC CMAKE BUILD FILE                            |
#   |                                                                           |
#   O---------------------------------------------------------------------------O

# --- CHECKS --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)
project(QRTC LANGUAGES CXX)

# Requires a 64-bit Computer
if (NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "Only 64-bit builds are supported.")
endif()

# Require supported CPU architecture (x86_64 or AArch64)
if (NOT (CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64|aarch64|arm64"))
    message(FATAL_ERROR
        "Only x86-64 (x86_64/AMD64) and AArch64 (aarch64/arm64) are supported. "
        "Detected: ${CMAKE_SYSTEM_PROCESSOR}"
    )
endif()

# Detect platform & compiler
if (WIN32)
    message(STATUS "Building on 64-bit Windows")

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
    message(STATUS "Building on macOS")

    # AppleClang reports as "AppleClang"
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
        message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} (version ${CMAKE_CXX_COMPILER_VERSION})")
    else ()
        message(FATAL_ERROR "Unsupported compiler on macOS: ${CMAKE_CXX_COMPILER_ID}")
    endif()

elseif (UNIX)
    message(STATUS "Building on Unix/Linux")

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

# Enforce C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- FILE LISTS ----------------------------------------------------------------
# Keep these explicit (nice for IDEs and for avoiding accidental file pickup).

set(QRTC_HEADERS

    "headers/vec3.hpp"
    "headers/color.hpp"
    "headers/ray.hpp"
)

set(QRTC_SOURCES

    "sources/vec3.cpp"
    "sources/color.cpp"
    "sources/ray.cpp"    
)

# --- TEST PROGRAMS -------------------------------------------------------------
# List each test program explicitly here.

add_executable(prog1

    "tests/prog1.cpp"
    ${QRTC_HEADERS}
    ${QRTC_SOURCES}

)
target_include_directories(prog1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/headers)

add_executable(prog2

    "tests/prog2.cpp"
    ${QRTC_HEADERS}
    ${QRTC_SOURCES}

)
target_include_directories(prog2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/headers)
