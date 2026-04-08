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

option(QRTC_BUILD_SHARED_LIB "Build QRTC as a shared library" OFF)
option(QRTC_BUILD_EXAMPLES "Build QRTC usage example programs" OFF)
option(QRTC_DYNAMIC_DISPATCH "Build Dynamic Dispatch for detected platform" OFF)

# --- ISA AND EXTENSION SPECIFIC FLAGS ------------------------------------------

