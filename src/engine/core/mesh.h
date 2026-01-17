#pragma once

#include "compiler.h"
#include "vertex.h"

#define PRIM_TRIANGLES 0
#define PRIM_TRI_STRIP 1
#define PRIM_QUADS     2

typedef HEADER_ALIGN(16) struct Mesh {
    Vertex* vertices;
    uint16_t* indices;

    uint16_t vertex_count;
    uint16_t index_count;

    uint16_t primitive_type;
} FOOTER_ALIGN(16) Mesh;

/**
 * Packages the position of a normal vector of three xyz floats
 * into a uint32_t
 */
static inline uint32_t pack_normal(float x, float y, float z) {
    uint8_t nx = (uint8_t)((x + 1.0f) * 127.5f);
    uint8_t ny = (uint8_t)((y + 1.0f) * 127.5f);
    uint8_t nz = (uint8_t)((z + 1.0f) * 127.5f);
    
    return (uint32_t)(nx | (ny << 8) | (nz << 16));
}

// Mesh* load_mesh(int mesh_id) {
//     Mesh* mesh = malloc(sizeof(Mesh));

//     // Logic to load and fill the area of memory for the mesh

//     return mesh;
// }
