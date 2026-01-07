#include "platform.h"
#include <SDL.h>
#include "../engine/input/mouse.h"

Platform* current_platform;

bool platform_init(Platform* p, const char* title, int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) != 0)
        return false;

    // Ask for a compatibility GL context; 1.1 calls will be present from opengl32.dll
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    p->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                 w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!p->window) return false;

    p->glctx = SDL_GL_CreateContext((SDL_Window*)p->window);
    if (!p->glctx) return false;

    SDL_GL_MakeCurrent((SDL_Window*)p->window, p->glctx);
    SDL_GL_SetSwapInterval(1);

    p->width = w; p->height = h;
    p->running = true;
    p->prev = SDL_GetTicks64();
    p->now = p->prev;

    current_platform = p;

    return true;
}

void platform_pump(Platform* p) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) 
    {
        // Causes the main program loop to exit.
        if (e.type == SDL_QUIT) p->running = false;
    
        // Exit the program if you hear the ESC key
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) p->running = false;

        if (e.type == SDL_MOUSEMOTION)
        {
            // Update the mouse position.
            mouse_set_pos(e.motion.x, e.motion.y);
        }
    }

    current_platform->prev = current_platform->now;
    current_platform->now = SDL_GetTicks64();
}

void platform_swap(Platform* p) {
    SDL_GL_SwapWindow((SDL_Window*)p->window);
}

void platform_shutdown(Platform* p) {
    SDL_GL_DeleteContext(p->glctx);
    SDL_DestroyWindow((SDL_Window*)p->window);
    SDL_Quit();
}

float platform_delta_seconds() {
    float dt = ((float)current_platform->now - (float)current_platform->prev) / 1000.0f;
    
    return dt;
}
