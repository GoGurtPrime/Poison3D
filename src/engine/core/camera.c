#include "camera.h"

void set_camera_transform(const camera_t *camera)
{
    // Set the camera transform
    glLoadIdentity();

    glTranslatef(
        camera->position[0], // X 
        camera->position[1], // Y
        camera->position[2]  // Z
    );
    
    glRotatef(camera->rotation[0], 1, 0, 0); // X
    glRotatef(camera->rotation[1], 0, 1, 0); // Y
    glRotatef(camera->rotation[2], 0, 0, 1); // Z
}
