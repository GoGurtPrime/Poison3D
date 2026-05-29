#pragma once

#include <stdlib.h>
#include <string.h>
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

static inline Mesh* mesh_create_cube(float size) {
    Mesh* mesh = (Mesh*)malloc(sizeof(Mesh));
    if (!mesh) return NULL;

    mesh->vertex_count = 24; // 6 faces * 4 verts
    mesh->index_count = 36;  // 6 faces * 2 tris * 3 indices
    mesh->primitive_type = 0; // Assuming 0 = TRIANGLES

    // Allocate aligned memory for vertices
    mesh->vertices = (Vertex*)malloc_aligned(sizeof(Vertex) * mesh->vertex_count);
    mesh->indices = (uint16_t*)malloc(sizeof(uint16_t) * mesh->index_count);

    if (!mesh->vertices || !mesh->indices) {
        // Handle allocation failure
        if (mesh->vertices) free_aligned(mesh->vertices);
        if (mesh->indices) free(mesh->indices);
        free(mesh);
        return NULL;
    }

    float h = size / 2.0f;
    uint32_t white = 0xFFFFFFFF;

    // Calculate packed normals per side
    uint32_t normal_z_pos = pack_normal(0, 0, 1);
    uint32_t normal_z_neg = pack_normal(0, 0, -1);
    uint32_t normal_y_pos = pack_normal(0, 1, 0);
    uint32_t normal_y_neg = pack_normal(0, -1, 0);
    uint32_t normal_x_pos = pack_normal(1, 0, 0);
    uint32_t normal_x_neg = pack_normal(-1, 0, 0);

    // Define vertices (Position, Normal, UV, Color)
    // UVs are set 0.0 to 1.0 for standard mapping
    Vertex cube_verts[24] = {
        // Front Face (Z+)
        { -h, -h,  h, normal_z_pos, 0.0f, 1.0f, white }, // Bottom Left
        {  h, -h,  h, normal_z_pos, 1.0f, 1.0f, white }, // Bottom Right
        {  h,  h,  h, normal_z_pos, 1.0f, 0.0f, white }, // Top Right
        { -h,  h,  h, normal_z_pos, 0.0f, 0.0f, white }, // Top Left

        // Back Face (Z-)
        {  h, -h, -h, normal_z_neg, 0.0f, 1.0f, white },
        { -h, -h, -h, normal_z_neg, 1.0f, 1.0f, white },
        { -h,  h, -h, normal_z_neg, 1.0f, 0.0f, white },
        {  h,  h, -h, normal_z_neg, 0.0f, 0.0f, white },

        // Top Face (Y+)
        { -h,  h,  h, normal_y_pos, 0.0f, 1.0f, white },
        {  h,  h,  h, normal_y_pos, 1.0f, 1.0f, white },
        {  h,  h, -h, normal_y_pos, 1.0f, 0.0f, white },
        { -h,  h, -h, normal_y_pos, 0.0f, 0.0f, white },

        // Bottom Face (Y-)
        { -h, -h, -h, normal_y_neg, 0.0f, 1.0f, white },
        {  h, -h, -h, normal_y_neg, 1.0f, 1.0f, white },
        {  h, -h,  h, normal_y_neg, 1.0f, 0.0f, white },
        { -h, -h,  h, normal_y_neg, 0.0f, 0.0f, white },

        // Right Face (X+)
        {  h, -h,  h, normal_x_pos, 0.0f, 1.0f, white },
        {  h, -h, -h, normal_x_pos, 1.0f, 1.0f, white },
        {  h,  h, -h, normal_x_pos, 1.0f, 0.0f, white },
        {  h,  h,  h, normal_x_pos, 0.0f, 0.0f, white },

        // Left Face (X-)
        { -h, -h, -h, normal_x_neg, 0.0f, 1.0f, white },
        { -h, -h,  h, normal_x_neg, 1.0f, 1.0f, white },
        { -h,  h,  h, normal_x_neg, 1.0f, 0.0f, white },
        { -h,  h, -h, normal_x_neg, 0.0f, 0.0f, white }
    };

    // Define Indices (Counter-Clockwise winding)
    // Every 4 vertices = 2 triangles (0,1,2) and (2,3,0)
    uint16_t cube_indices[36] = {
        // Front
        0, 1, 2,  2, 3, 0,
        // Back
        4, 5, 6,  6, 7, 4,
        // Top
        8, 9, 10, 10, 11, 8,
        // Bottom
        12, 13, 14, 14, 15, 12,
        // Right
        16, 17, 18, 18, 19, 16,
        // Left
        20, 21, 22, 22, 23, 20
    };

    // Copy data to heap
    memcpy(mesh->vertices, cube_verts, sizeof(cube_verts));
    memcpy(mesh->indices, cube_indices, sizeof(cube_indices));

    return mesh;
}

// Mesh* load_mesh(int mesh_id) {
//     Mesh* mesh = malloc(sizeof(Mesh));

//     // Logic to load and fill the area of memory for the mesh

//     return mesh;
// }
