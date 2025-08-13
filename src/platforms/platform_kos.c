#include "platform.h"
#include <kos.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glkos.h>


bool platform_init(Platform* p, const char* title, int w, int h) {
    /* Get basic stuff initialized */
    //glKosInit();

    p->running = true;

    return true;
}

void platform_pump(Platform* p) {
}

void platform_swap(Platform* p) {
    GLenum e; 
    while ((e = glGetError()) != GL_NO_ERROR) dbglog(DBG_ERROR, "GL error: 0x%04x\n", e);

}

void platform_shutdown(Platform* p) {
    
}

float platform_delta_seconds(Platform* p) {
    float dt = (float)(p->now - p->prev);
    p->prev = p->now;
    return dt;
}
