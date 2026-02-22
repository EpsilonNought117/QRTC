#   O---------------------------------------------------------------------------O
#   |                                                                           |
#   |                          QRTC CMAKE BUILD FILE                            |
#   |                                                                           |
#   O---------------------------------------------------------------------------O

# --- CHECKS --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)
project(QRTC LANGUAGES C)

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

    if (CMAKE_C_COMPILER_ID STREQUAL "Clang" OR
        CMAKE_C_COMPILER_ID STREQUAL "AppleClang")
        message(STATUS "Compiler: ${CMAKE_C_COMPILER_ID} (version ${CMAKE_C_COMPILER_VERSION})")
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

# --- C STANDARD ---------------------------------------------------------------

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# --- FILE LISTS ----------------------------------------------------------------

set(QRTC_HEADERS

    "headers/vec3.h"
    "headers/color.h"
)

set(QRTC_SOURCES

    "sources/vec3.c"
    "sources/color.c"
)

# --- TEST PROGRAMS -------------------------------------------------------------

add_executable(prog1
    "tests/prog1.c"
    ${QRTC_SOURCES}
)
target_include_directories(prog1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/headers)
