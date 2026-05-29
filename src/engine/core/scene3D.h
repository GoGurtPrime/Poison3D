#pragma once

#include "transform.h"
#include "matrix4x4.h"

typedef struct Scene3D {
    // Identifier for this scene
    int id;

    // The number of entities in the scene
    int entity_count;

    // Track features/behaviors of entities
    int entity_flags[64];

    // Entity transforms
    Transform entity_transforms[64];

    // Track which entities need their modelview matrix updated
    // Up to 128 entities, each bit is a toggle.
    uint32_t dirty_modelview_indices[4];
    Matrix4x4 entity_modelviews[64];
    
    // Everything after here is still a WIP, deciding on what features
    // I will implement for things like lighting, triggers, etc.

    // Track features/props of lights
    int light_flags[8];

    // Transforms for each light
    Transform light_transforms[8];

    // Where the player starts in the world
    Transform player_spawn_transform;

    // TODO: Sound Volumes
    // TODO: Lighting Volumes?
    // TODO: Trigger Volumes
    // TODO: Pickups/Dispensable Items, could track as entity with certain flags
    //       Activated by a trigger volume to despawn the pickup.
} Scene;
