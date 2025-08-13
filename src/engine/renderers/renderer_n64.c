#include "renderer.h"
#include "../core/camera.h"
#include <math.h>
#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <rspq_profile.h>

static float t = 0.f;
static uint64_t frames = 0;

static camera_t camera;

static const GLfloat environment_color[] = {0.1f, 0.03f, 0.2f, 1.f};

// Represents diffuse lights, with their position and intensity.
static const GLfloat light_diffuse[8][4] = {
    {1.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 1.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, 0.0f, 1.0f},
    {1.0f, 0.0f, 1.0f, 1.0f},
    {0.0f, 1.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, 1.0f, 1.0f},
};

void renderer_init(int width, int height) 
{
    camera.distance = -10.0f;
    camera.rotation = 0.0f;

    float aspect_ratio = (float)display_get_width() / (float)display_get_height();
    float near_plane = 1.0f;
    float far_plane = 50.0f;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-near_plane*aspect_ratio, near_plane*aspect_ratio, -near_plane, near_plane, near_plane, far_plane);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, environment_color);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    float light_radius = 10.0f;

    for (int i = 0; i < 3; i++)
    {
        glEnable(GL_LIGHT0 + i);
        glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, light_diffuse[i]);
        glLightf(GL_LIGHT0 + i, GL_LINEAR_ATTENUATION, 2.0f / light_radius);
        glLightf(GL_LIGHT0 + i, GL_QUADRATIC_ATTENUATION, 1.0f / (light_radius * light_radius));
    }

    GLfloat mat_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);

    glFogf(GL_FOG_START, 5);
    glFogf(GL_FOG_END, 20);
    glFogfv(GL_FOG_COLOR, environment_color);

    glEnable(GL_MULTISAMPLE_ARB);
}

void renderer_render(void) 
{
    t += 0.016f;
    surface_t *disp = display_get();
    surface_t *zbuf = display_get_zbuf();
    
    rdpq_attach(disp, zbuf);

    gl_context_begin();

    glClearColor(environment_color[0], environment_color[1], environment_color[2], environment_color[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    camera_transform(&camera);

    // Set some global render modes that we want to apply to all models
    // glEnable(GL_LIGHTING);
    // glEnable(GL_NORMALIZE);
    // glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);

    rdpq_set_mode_standard();
    rdpq_mode_filter(FILTER_BILINEAR);

    glRotatef(sinf(t) * 45.0f, 0.0f, 0.0f, 1.0f);

    float size = 2.0f;

    glBegin(GL_TRIANGLES);
        glColor3f(1.f, .0f, .0f);

        // Front face (Z+)
        glVertex3f(-size, -size,  size);
        glVertex3f( size, -size,  size);
        glVertex3f( size,  size,  size);

        glVertex3f(-size, -size,  size);
        glVertex3f( size,  size,  size);
        glVertex3f(-size,  size,  size);

        glColor3f(0.0f, 1.0f, 0.0f);

        // Back face (Z-)
        glVertex3f( size, -size, -size);
        glVertex3f(-size, -size, -size);
        glVertex3f(-size,  size, -size);

        glVertex3f( size, -size, -size);
        glVertex3f(-size,  size, -size);
        glVertex3f( size,  size, -size);

        glColor3f(0.0f, 0.0f, 1.0f);

        // Left face (X-)
        glVertex3f(-size, -size, -size);
        glVertex3f(-size, -size,  size);
        glVertex3f(-size,  size,  size);

        glVertex3f(-size, -size, -size);
        glVertex3f(-size,  size,  size);
        glVertex3f(-size,  size, -size);

        glColor3f(1.0f, 1.0f, 0.0f);

        // Right face (X+)
        glVertex3f( size, -size,  size);
        glVertex3f( size, -size, -size);
        glVertex3f( size,  size, -size);

        glVertex3f( size, -size,  size);
        glVertex3f( size,  size, -size);
        glVertex3f( size,  size,  size);

        glColor3f(1.0f, 0.0f, 1.0f);

        // Top face (Y+)
        glVertex3f(-size,  size,  size);
        glVertex3f( size,  size,  size);
        glVertex3f( size,  size, -size);

        glVertex3f(-size,  size,  size);
        glVertex3f( size,  size, -size);
        glVertex3f(-size,  size, -size);

        glColor3f(1.0f, 1.0f, 1.0f);

        // Bottom face (Y-)
        glVertex3f(-size, -size, -size);
        glVertex3f( size, -size, -size);
        glVertex3f( size, -size,  size);

        glVertex3f(-size, -size, -size);
        glVertex3f( size, -size,  size);
        glVertex3f(-size, -size,  size);
    glEnd();

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
