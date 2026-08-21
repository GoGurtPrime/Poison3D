#pragma once

#include "transform.h"
#include "camera.h"
#include "matrix4x4.h"
#include <stdint.h>

#define MAX_ENTITY_COUNT 64

typedef struct {
    int id;

    char scene_flags;

    int entity_count;
    int entity_flags[MAX_ENTITY_COUNT];
    Transform entity_transforms[MAX_ENTITY_COUNT];

    // Track which entities need their modelview matrix updated
    // Up to 128 entities, each bit is a toggle.
    uint32_t dirty_modelview_indices[4];
    Matrix4x4 entity_modelviews[64];

    camera_t *camera_transform;
} scene_t;

void scene_initialize();

void set_and_load_scene(char* scene_name);

void save_scene(char* scene_file_path);

scene_t* get_scene();
