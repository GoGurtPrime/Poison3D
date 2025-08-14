#include "renderer.h"
#include <math.h>
#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <rspq_profile.h>
#include "../../platforms/platform.h"
#include "renderer_common.h"

// Optional for RSP testing
//static uint64_t frames = 0;

void renderer_init(int width, int height) 
{
    renderer_common_setup(display_get_width(), display_get_height());

    glEnable(GL_MULTISAMPLE_ARB);
}

void renderer_render(void) 
{    
    surface_t *disp = display_get();
    surface_t *zbuf = display_get_zbuf();
    
    rdpq_attach(disp, zbuf);

    rdpq_set_mode_standard();
    rdpq_mode_filter(FILTER_BILINEAR);

    gl_context_begin();

    renderer_common_draw();

    gl_context_end();

    rdpq_detach_show();

    // rspq_profile_next_frame();

    // if (((frames++) % 60) == 0) {
    //     rspq_profile_dump();
    //     rspq_profile_reset();
    //     debugf("frame %lld\n", frames);
    // }
}

void renderer_shutdown(void) {}
