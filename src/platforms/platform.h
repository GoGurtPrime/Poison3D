#pragma once
#include <stdbool.h>

typedef struct Platform {
    void* window; // SDL_Window*
    void* glctx;  // SDL_GLContext
    int width, height;
    bool running;
    unsigned long now, prev;
} Platform;

bool platform_init(Platform* p, const char* title, int w, int h);
void platform_pump(Platform* p);
void platform_swap(Platform* p);
void platform_shutdown(Platform* p);
float platform_delta_seconds();
