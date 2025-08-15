// main.c — MSVC-safe: macro sizes, no VLA, no enum sizes.

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ---- compile-time constants (macros) ---- */
#define FONT_W         8
#define FONT_H         13
#define GLYPH_FIRST    ('A')
#define GLYPH_LAST     ('Z')
#define GLYPH_COUNT    ((GLYPH_LAST) - (GLYPH_FIRST) + 1)
#define TMP_MAX        64   /* temp raster buffer width/height */

/* ---- helpers ---- */
static unsigned char* read_file(const char* p, size_t* sz) {
    FILE* f = fopen(p, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long n = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (n <= 0) { fclose(f); return NULL; }
    unsigned char* buf = (unsigned char*)malloc((size_t)n);
    if (!buf) { fclose(f); return NULL; }
    fread(buf, 1, (size_t)n, f);
    fclose(f);
    *sz = (size_t)n;
    return buf;
}

static void usage(const char* exe) { fprintf(stderr, "Usage: %s input.ttf -o output.h\n", exe); }

int main(int argc, char** argv) {
    if (argc < 4) { usage(argv[0]); return 1; }
    const char* in_path = NULL;
    const char* out_path = NULL;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) out_path = argv[++i];
        else if (!in_path) in_path = argv[i];
    }
    if (!in_path || !out_path) { usage(argv[0]); return 1; }

    size_t ttf_sz = 0;
    unsigned char* ttf = read_file(in_path, &ttf_sz);
    if (!ttf) { fprintf(stderr, "Failed to read %s\n", in_path); return 1; }

    stbtt_fontinfo font;
    if (!stbtt_InitFont(&font, ttf, stbtt_GetFontOffsetForIndex(ttf, 0))) {
        fprintf(stderr, "Invalid TTF\n"); free(ttf); return 1;
    }

    /* scale for our target output height */
    const float scale = stbtt_ScaleForPixelHeight(&font, (float)FONT_H);

    /* storage: 1 byte per output row (MSB-first bits) */
    unsigned char letters[GLYPH_COUNT][FONT_H];
    unsigned char glyph_space[FONT_H];
    memset(glyph_space, 0, sizeof(glyph_space));

    /* working buffer for a glyph (8-bit coverage) */
    const size_t tmp_sz = (size_t)TMP_MAX * (size_t)TMP_MAX;
    unsigned char* tmp = (unsigned char*)malloc(tmp_sz);
    if (!tmp) { free(ttf); return 1; }

    for (int c = GLYPH_FIRST; c <= GLYPH_LAST; ++c) {
        const int gi = c - GLYPH_FIRST;

        int x0,y0,x1,y1;
        stbtt_GetCodepointBitmapBox(&font, c, scale, scale, &x0,&y0,&x1,&y1);
        const int gw = x1 - x0, gh = y1 - y0;

        if (gw <= 0 || gh <= 0 || gw > TMP_MAX || gh > TMP_MAX) {
            memset(letters[gi], 0, FONT_H);
            continue;
        }

        memset(tmp, 0, tmp_sz);
        stbtt_MakeCodepointBitmap(&font, tmp, gw, gh, gw, scale, scale, c);

        /* downsample gw×gh -> FONT_W×FONT_H, 1bpp MSB-first per row */
        for (int oy = 0; oy < FONT_H; ++oy) {
            unsigned char row = 0;
            for (int ox = 0; ox < FONT_W; ++ox) {
                int sx = (int)((ox + 0.5f) * (float)gw / (float)FONT_W);
                int sy = (int)((oy + 0.5f) * (float)gh / (float)FONT_H);
                if (sx < 0) sx = 0; if (sx >= gw) sx = gw - 1;
                if (sy < 0) sy = 0; if (sy >= gh) sy = gh - 1;

                const unsigned char cov = tmp[sy * gw + sx];
                const int bit = (cov >= 128);
                row |= (unsigned char)(bit << (7 - ox)); /* MSB-first */
            }
            letters[gi][FONT_H - 1 - oy] = row;  /* flip vertical byte order for your renderer */
        }
    }

    /* write header */
    FILE* out = fopen(out_path, "wb");
    if (!out) { fprintf(stderr, "Failed to open %s for write\n", out_path); free(tmp); free(ttf); return 1; }

    fprintf(out, "/* Auto-generated from %s: %dx%d 1bpp ASCII (A..Z + space) */\n", in_path, FONT_W, FONT_H);
    fprintf(out, "#ifndef TTF2BITMAP_FONT_8x13_H\n#define TTF2BITMAP_FONT_8x13_H\n\n");
    fprintf(out, "#include <GL/gl.h>\n\n");
    fprintf(out, "#ifdef __cplusplus\nextern \"C\" {\n#endif\n\n");
    fprintf(out, "enum { FONT_FIRST = '%c', FONT_LAST = '%c', FONT_COUNT = %d, FONT_W = %d, FONT_H = %d };\n\n",
            GLYPH_FIRST, GLYPH_LAST, GLYPH_COUNT, FONT_W, FONT_H);

    /* space[] */
    fprintf(out, "static const GLubyte space[%d] = {", FONT_H);
    for (int i = 0; i < FONT_H; ++i) fprintf(out, "0x%02X%s", glyph_space[i], (i+1==FONT_H)?"":", ");
    fprintf(out, "};\n\n");

    /* letters[][FONT_H] */
    fprintf(out, "static const GLubyte letters[%d][%d] = {\n", GLYPH_COUNT, FONT_H);
    for (int g = 0; g < GLYPH_COUNT; ++g) {
        fprintf(out, "  {");
        for (int r = 0; r < FONT_H; ++r) fprintf(out, "0x%02X%s", letters[g][r], (r+1==FONT_H)?"":", ");
        fprintf(out, "}%s /* '%c' */\n", (g+1==GLYPH_COUNT)?"":",", (char)(GLYPH_FIRST + g));
    }
    fprintf(out, "};\n\n");

    fprintf(out, "#ifdef __cplusplus\n}\n#endif\n");
    fprintf(out, "#endif /* TTF2BITMAP_FONT_8x13_H */\n");
    fclose(out);

    fprintf(stdout, "Wrote %s (A..Z + space, %dx%d)\n", out_path, FONT_W, FONT_H);
    free(tmp);
    free(ttf);
    return 0;
}
