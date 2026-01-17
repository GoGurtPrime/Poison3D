#pragma once

#include "compiler.h"

typedef HEADER_ALIGN(32) struct Vertex {
    float x, y, z;      // Position
    uint32_t normal;    // Packed normal
    float u, v;
    uint32_t color;     // RGBA
} FOOTER_ALIGN(32) Vertex;
