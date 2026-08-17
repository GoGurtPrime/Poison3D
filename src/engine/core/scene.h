#pragma once

#include "transform.h"

#define MAX_ENTITY_COUNT 64

typedef struct {
    int id;

    char scene_flags = 0b00000000;

    int entity_count;
    int entity_flags[MAX_ENTITY_COUNT];
    Transform entity_transforms[MAX_ENTITY_COUNT];

} scene_t;

void scene_tick();

/**
 * @brief Call to render the scene. Shoudld be called for
 *        every iteration of the main loop. 
 */
void scene_draw();

/**
 * @brief Call for every iteration in the main loop,
 *        even when paused. Used for gameplay logic. 
 */
void scene_update();
