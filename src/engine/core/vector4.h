#pragma once

#include "compiler.h"
#include "vector3.h"

typedef HEADER_ALIGN(16) union {
    struct {
        float x, y, z, w;
    };

    float components[4];
} FOOTER_ALIGN(16) Vector4;
