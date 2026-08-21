#include "scene.h"
#include <stdlib.h>

static scene_t *scene;

void scene_initialize()
{
    scene = malloc(sizeof(scene_t));
    scene->camera_transform = malloc(sizeof(camera_t));

    scene->id = 0;
    scene->scene_flags = 0b00000000;
    scene->entity_count = 0;

    scene->dirty_modelview_indices[0] = 0;
    scene->dirty_modelview_indices[1] = 0;
    scene->dirty_modelview_indices[2] = 0;
    scene->dirty_modelview_indices[3] = 0;

    scene->camera_transform->position[0] = 0.f;
    scene->camera_transform->position[1] = 0.f;
    scene->camera_transform->position[2] = -10.f;

    scene->camera_transform->rotation[0] = 0.f;
    scene->camera_transform->rotation[1] = 60.f;
    scene->camera_transform->rotation[2] = 0.f;
}

void set_and_load_scene(char* scene_name)
{

}

void save_scene(char* scene_file_path)
{

}

scene_t* get_scene()
{
    return scene;
}
