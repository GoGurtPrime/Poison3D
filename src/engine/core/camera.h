#ifndef CAMERA_H
#define CAMERA_H

#ifdef _WIN32
  #include <windows.h>  // Must be included before GL on Windows
#endif

#include <GL/gl.h>
#include <GL/glu.h>

typedef struct {
    float distance;
    float rotation;
} camera_t;

void camera_transform(const camera_t *camera)
{
    // Set the camera transform
    glLoadIdentity();
    gluLookAt(
        0, -camera->distance, -camera->distance,
        0, 0, 0,
        0, 1, 0);
    glRotatef(camera->rotation, 0, 1, 0);
}

#endif
