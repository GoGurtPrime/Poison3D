#include "renderer.h"
#include "renderer_common.h"

#ifdef _WIN32
    #include <windows.h>  // Must be included before GL on Windows
#endif

#include <GL/gl.h>
#include <GL/GLU.h>

#include <math.h>


static long frames = 0;

void renderer_init(int width, int height) {
    renderer_common_setup(width, height);
    
}

void renderer_render(void) {


    // Set some global render modes that we want to apply to all models
    // glEnable(GL_LIGHTING);
    // glEnable(GL_NORMALIZE);
    // glEnable(GL_CULL_FACE);

    glPushMatrix();

    renderer_common_draw();

    glPopMatrix();
}

void renderer_shutdown(void) {}
