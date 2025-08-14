#include "renderer.h"
#include "renderer_common.h"

#ifdef _WIN32
    #include <windows.h>  // Must be included before GL on Windows
#endif

#include <GL/gl.h>
#include <GL/GLU.h>

#include <math.h>

void renderer_init(int width, int height) 
{
    renderer_common_setup(width, height);   
}

void renderer_render(void) 
{
    glPushMatrix();

    renderer_common_draw();

    glPopMatrix();
}

void renderer_shutdown(void) {}
