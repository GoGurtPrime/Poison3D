#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include "platform.h"
#include <libdragon.h>
#include <rspq_profile.h>

bool platform_init(Platform* p, const char* title, int w, int h) {
    //console_init();

    // debug_init_isviewer();
    // debug_init_usblog();

    // console_set_debug(true);
    
    dfs_init(DFS_DEFAULT_LOCATION);
    
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, FILTERS_RESAMPLE_ANTIALIAS_DEDITHER);
    
    rdpq_init();
    gl_init();
    
    //rspq_profile_start();

    joypad_init();

    p->running = true;

    return true;
}

void platform_pump(Platform* p) {
}

void platform_swap(Platform* p) {
    //rsqp_wait();
}

void platform_shutdown(Platform* p) {
    
}

float platform_delta_seconds(Platform* p) {
    float dt = (float)(p->now - p->prev);
    p->prev = p->now;
    return dt;
}
