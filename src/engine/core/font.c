#include "font.h"

#ifdef _WIN32
    #include <windows.h>  // Must be included before GL on Windows
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <string.h>
#include "../image-formats/image_format_tga.h"

GLuint font_list;

void font_make()
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    GLuint i, j, z;

    font_list = glGenLists(128);

    GLubyte *letter;

    char *base_path = "C:\\Users\\colin\\src\\poison3d\\src\\assets\\fonts\\Consolas\\";

    for (i = 0, j = 'a'; i < 26; i++,j++)
    {
        char *path = strdup(base_path);
        
        strcat(strcat(path, &j), ".tga");

        ImageTga image = image_load_tga(path);
        int pixel_count = image.header.height * image.header.width;
        
        letter = malloc(pixel_count * sizeof(GLubyte) * 4);

        int m;
        
        for (m = 0; m < pixel_count; m++)
        {
            letter[4*m + 0] = image.pixels[m].r;
            letter[4*m + 1] = image.pixels[m].g;
            letter[4*m + 2] = image.pixels[m].b;
            letter[4*m + 3] = image.pixels[m].a;
        }

        glNewList(font_list + j, GL_COMPILE);
            glDrawPixels(image.header.width, image.header.height, GL_RGBA, GL_UNSIGNED_BYTE, letter);
        glEndList();

        free(letter);
    }
}

void font_init()
{
    glShadeModel(GL_FLAT);

    font_make();
}

void font_print_string(char *s, int x, int y)
{
    glPushAttrib(GL_LIST_BIT);
    glListBase(font_list);

    // TODO: Pass this in instead, maybe default in the font?
    int font_spacing = 45;

    for (GLint i = 0; i < strlen(s); i++)
    {
        if (s[i] == ' ')
            continue;

        glRasterPos2i(x + (i * font_spacing), y);
        
        glCallLists(1, GL_UNSIGNED_BYTE, (GLubyte *) &s[i]);
    }

    glPopAttrib();
}
