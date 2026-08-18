#include "platform.h"
#include <kos.h>
#include <GL/gl.h>
#include <GL/glkos.h>
#include <GL/glu.h>
#include <GL/glext.h>

Platform *platform;

static void on_press_start(uint8_t address, uint32_t buttons) {
    (void)address;
    (void)buttons;
    // Shut down.
    platform->running = false;
}

bool platform_init(Platform* p, const char* title, int w, int h) 
{
    platform = p;

    glKosInit();

    p->running = true;

    /* Subscribe a callback to be notified whenever the start button is pressed
    on any connected controller. */
    cont_btn_callback(0, CONT_START, on_press_start);

    return true;
}

void platform_pump(Platform* p) 
{
     
}

void platform_swap(Platform* p) 
{
    // GLdc flush/swap
    glKosSwapBuffers();            
}

void platform_shutdown(Platform* p) 
{
    
}

float platform_delta_seconds(Platform* p) 
{
    float dt = (float)(p->now - p->prev);
    p->prev = p->now;
    return dt;
}
