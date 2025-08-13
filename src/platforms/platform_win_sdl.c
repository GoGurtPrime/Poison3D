#include "platform.h"
#include <SDL.h>

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
    p->prev = SDL_GetTicks64() / 1000.0;
    p->now = p->prev;
    return true;
}

void platform_pump(Platform* p) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) p->running = false;
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) p->running = false;
    }
    p->now = SDL_GetTicks64() / 1000.0;
}

void platform_swap(Platform* p) {
    SDL_GL_SwapWindow((SDL_Window*)p->window);
}

void platform_shutdown(Platform* p) {
    SDL_GL_DeleteContext(p->glctx);
    SDL_DestroyWindow((SDL_Window*)p->window);
    SDL_Quit();
}

float platform_delta_seconds(Platform* p) {
    float dt = (float)(p->now - p->prev);
    p->prev = p->now;
    return dt;
}
