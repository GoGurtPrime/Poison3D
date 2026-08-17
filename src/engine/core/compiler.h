#pragma once

// This file contains macro definitions per the compiler being used

// If building with MSC (Visual C/C++)
#if defined(_MSC_VER)
    #define HEADER_ALIGN(n) __declspec(align(n))
    #define FOOTER_ALIGN(n) 
    #define INLINE __forceinline
// If compiling using GCC or CLANG
#elif defined(__GNUC__) || defined(__clang__)
    #define HEADER_ALIGN(n)
    #define FOOTER_ALIGN(n) __attribute__((aligned(n)))
    #define INLINE static inline __attribute__((always_inline))
#else
    #define HEADER_ALIGN(n)
    #define FOOTER_ALIGN(n)
    #define INLINE static inline
#endif

// Platform detection
#if defined(__N64__) || defined(N64)
    #define POISON_PLATFORM_N64
#elif defined(_arch_dreamcast) || defined(__DREAMCAST__)
    #define POISON_PLATFORM_DREAMCAST
#elif defined(_WIN32)
    #define POISON_PLATFORM_WINDOWS
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#elif defined(__APPLE__)
    #define POISON_PLATFORM_MAC
    #include <mach-o/dyld.h>
#elif defined(__linux__)
    #define POISON_PLATFORM_LINUX
    #include <unistd.h>
#endif