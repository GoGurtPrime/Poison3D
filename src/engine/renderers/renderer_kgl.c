#include "renderer.h"
#include "../core/camera.h"
#include "renderer_common.h"
#include <kos.h>
#include <GL/gl.h>
#include <GL/glkos.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <math.h>

void renderer_init(int width, int height) 
{
    renderer_common_setup(width, height);
    glViewport(0, 0, 640, 480);
}

void renderer_render(void) 
{
    glPushMatrix();

    renderer_common_draw();

    glPopMatrix();
}

void renderer_shutdown(void) {}
