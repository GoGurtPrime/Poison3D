#ifndef POISON_FILESYSTEM_H
#define POISON_FILESYSTEM_H 1

#ifdef _WIN32
    #include <windows.h>
#endif

    #include <GL/gl.h>
    #include <GL/glu.h> 

    GLubyte *read_asset_bytes(char *path);
#endif