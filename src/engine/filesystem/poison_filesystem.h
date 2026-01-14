#pragma once
#ifdef _WIN32
    #include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h> 

GLubyte *read_asset_bytes(char *path);
