#pragma once

#ifdef _WIN32
    #include <windows.h>  // Must be included before GL on Windows
#endif

#include <GL/gl.h>
#include <GL/GLU.h>

typedef struct UiRect {
    GLint x, y, w, h, r, g, b, a;
    GLboolean use_hover;
} UiRect;

typedef struct UiPage {
    UiRect rects[];    
} UiPage;
