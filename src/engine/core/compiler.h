#pragma once

#if defined(_MSC_VER)
    #define HEADER_ALIGN(n) __declspec(align(n))
    #define FOOTER_ALIGN(n) 
    #define INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
    #define HEADER_ALIGN(n)
    #define FOOTER_ALIGN(n) __attribute__((aligned(n)))
    #define INLINE static inline __attribute__((always_inline))
#else
    #define HEADER_ALIGN(n)
    #define FOOTER_ALIGN(n)
    #define INLINE static inline
#endif
