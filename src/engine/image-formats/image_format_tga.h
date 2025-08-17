#ifndef IMAGE_FORMAT_TGA_H
#define IMAGE_FORMAT_TGA_H

#ifdef _WIN32
    #include <windows.h>
#endif

    #include <GL/gl.h>
    #include <GL/glu.h>

    #include <stdint.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <errno.h>

    typedef struct {
        uint8_t  idlength;
        uint8_t  colourmaptype;
        uint8_t  datatypecode;
        uint16_t colourmaporigin;
        uint16_t colourmaplength;
        uint8_t  colourmapdepth;
        uint16_t x_origin;
        uint16_t y_origin;
        uint16_t width;
        uint16_t height;
        uint8_t  bitsperpixel;
        uint8_t  imagedescriptor;
    } ImageHeaderTga;

    typedef struct {
        unsigned char r,g,b,a;
    } Pixel;

    typedef struct {
        ImageHeaderTga header;
        Pixel *pixels;
    } ImageTga;

    ImageTga image_load_tga(char *path);

    void merge_bytes(Pixel *pixel, unsigned char *p, int bytes);
#endif
