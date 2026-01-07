#include "image_format_tga.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE_IMAGE_HEADER_TGA 18

ImageTga image_load_tga(char *path)
{
    ImageTga img = {0};
    
    FILE *p_file = fopen(path, "rb");
    
    uint8_t buffer[18] = {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    };

    if (p_file == NULL)
    {
        printf("Failed to open TGA file at ");
        printf(path);
        printf("\n");

        return img;
    }

    fread(buffer, 1, 18, p_file);

    img.header.idlength = buffer[0];
    img.header.colourmaptype = buffer[1];
    img.header.datatypecode = buffer[2];
    img.header.colourmaporigin = buffer[3] | buffer[4] << 8;
    img.header.colourmaplength = buffer[5] | buffer[6] << 8;
    img.header.colourmapdepth = buffer[7];
    img.header.x_origin = buffer[8] | buffer[9] << 8;
    img.header.y_origin = buffer[10] | buffer[11] << 8;
    img.header.width = buffer[12] | buffer[13] << 8;
    img.header.height = buffer[14] | buffer[15] << 8;
    img.header.bitsperpixel = buffer[16];
    img.header.imagedescriptor = buffer[17];

    int pixel_count = img.header.width * img.header.height;

    img.pixels = malloc(pixel_count * sizeof(Pixel));

    for (int i = 0; i < pixel_count; i++) {
        img.pixels[i].r = 0;
        img.pixels[i].g = 0;
        img.pixels[i].b = 0;
        img.pixels[i].a = 0;
    }

    int skip_bytes = img.header.idlength;
    skip_bytes += img.header.colourmapdepth * img.header.colourmaplength;
    
    fseek(p_file, skip_bytes, SEEK_CUR);

    int bytes2read, n, i, j = 0;
    unsigned char p[5];
    n = 0;

    bytes2read = img.header.bitsperpixel / 8;

    while (n < pixel_count) {
        if (img.header.datatypecode == 2) {                     /* Uncompressed */
            if (fread(p,1,bytes2read,p_file) != bytes2read) {
                fprintf(stderr,"Unexpected end of file at pixel %d\n",i);
                exit(-1);
            }
            
            merge_bytes(&(img.pixels[n]),p,bytes2read);
            n++;
        } else if (img.header.datatypecode == 10) {             /* Compressed */
            if (fread(p,1,bytes2read+1,p_file) != bytes2read+1) {
                fprintf(stderr,"Unexpected end of file at pixel %d\n",i);
                exit(-1);
            }
            
            j = p[0] & 0x7f;
            merge_bytes(&(img.pixels[n]),&(p[1]),bytes2read);
            
            n++;

            if (p[0] & 0x80) {         /* RLE chunk */
                for (i=0;i<j;i++) {
                    merge_bytes(&(img.pixels[n]),&(p[1]),bytes2read);
                    n++;
                }
            } else {                   /* Normal chunk */
                for (i=0;i<j;i++) {
                    if (fread(p,1,bytes2read,p_file) != bytes2read) {
                        fprintf(stderr,"Unexpected end of file at pixel %d\n",i);
                        exit(-1);
                    }
                    merge_bytes(&(img.pixels[n]),p,bytes2read);
                    n++;
                }
            }
        }
    }

    fclose(p_file);

    return img;
}

void merge_bytes(Pixel *pixel, unsigned char *p, int bytes)
{
   if (bytes == 4) {
      pixel->r = p[2];
      pixel->g = p[1];
      pixel->b = p[0];
      pixel->a = p[3];
   } else if (bytes == 3) {
      pixel->r = p[2];
      pixel->g = p[1];
      pixel->b = p[0];
      pixel->a = 255;
   } else if (bytes == 2) {
      pixel->r = (p[1] & 0x7c) << 1;
      pixel->g = ((p[1] & 0x03) << 6) | ((p[0] & 0xe0) >> 2);
      pixel->b = (p[0] & 0x1f) << 3;
      pixel->a = (p[1] & 0x80);
   }
}
