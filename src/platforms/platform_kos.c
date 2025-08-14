#include "platform.h"
#include <kos.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glkos.h>


bool platform_init(Platform* p, const char* title, int w, int h) {
    // TODO: Init for Dreamcast
    // This would be a decent spot for initializing an input system
    // or other systems such as audio.
    glKosInit();
    p->running = true;

    return true;
}

void platform_pump(Platform* p) {
}

void platform_swap(Platform* p) {
    // GLdc flush/swap
    glKosSwapBuffers();            
}

void platform_shutdown(Platform* p) {
    
}

float platform_delta_seconds(Platform* p) {
    float dt = (float)(p->now - p->prev);
    p->prev = p->now;
    return dt;
}
