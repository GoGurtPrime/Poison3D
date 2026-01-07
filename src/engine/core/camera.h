#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#ifdef _WIN32
  #include <windows.h>  // Must be included before GL on Windows
#endif

#include <GL/gl.h>
#include <GL/glu.h>

typedef struct {
    float position[3];
    float rotation[3];
} camera_t;

void set_camera_transform(const camera_t *camera);

#endif
