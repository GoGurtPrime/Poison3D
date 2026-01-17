#pragma once

#include "compiler.h"
#include "vector4.h"

typedef HEADER_ALIGN(32) union {
    Vector4 row[4];
    float m[16];

    struct {
        Vector4 r0, r1, r2, r3;
    };
} FOOTER_ALIGN(32) Matrix4x4;

static inline Matrix4x4 matrix_4x4_identity() {
    return (Matrix4x4){
        .m = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        }
    };
}
