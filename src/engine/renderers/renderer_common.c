#include "renderer_common.h"
#include "../core/camera.h"
#ifdef _WIN32
    #include <windows.h>  // Must be included before GL on Windows
    #include <GL/gl.h>
    #include <GL/GLU.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif
#include "../../platforms/platform.h"
#include <math.h>
#include "../core/font.h"
#include "../input/mouse.h"

static float t = 0.f;

static camera_t camera;

static const GLfloat environment_color[] = {0.03f, 0.03f, 0.03f, 1.f};

// Represents diffuse lights, with their position and intensity.
static const GLfloat light_diffuse[8][4] = {
    {1.0f, 0.951f, 0.75f, 0.1f},
    {1.0f, 0.951f, 0.75f, 0.1f},
    {1.0f, 0.951f, 0.75f, 0.1f},
    {1.0f, 0.951f, 0.75f, 0.1f},
    {1.0f, 0.951f, 0.75f, 0.1f},
    {1.0f, 0.951f, 0.75f, 0.1f},
    {1.0f, 0.951f, 0.75f, 0.1f},
    {1.0f, 0.951f, 0.75f, 0.1f},
};

// Draw a translucent quad at (x, y) with size (w, h).
// Assumes you're using an orthographic 2D setup.
// 'y' is the bottom edge if your coordinate system has Y-up.
void draw_quad(float x, float y, float w, float h,
              float r, float g, float b, float a)
{
    glColor4f(r, g, b, a);
    glBegin(GL_QUADS);
        glVertex2f(x,     y + h); // top-left
        glVertex2f(x + w, y + h); // top-right
        glVertex2f(x + w, y    ); // bottom-right
        glVertex2f(x,     y    ); // bottom-left
    glEnd();
}

void renderer_common_setup(int width, int height)
{
    camera.position[0] = 0.0f;
    camera.position[1] = 0.0f;
    camera.position[2] = -10.0f;
    
    camera.rotation[0] = 0.0f;
    camera.rotation[1] = 60.0f;
    camera.rotation[2] = 0.0f;

    glClearColor(0.0f, 0.0f, 0.3f, 1.0f);

    float aspect_ratio = (float)width / (float)height;
    float near_plane = 0.1f;
    float far_plane = 60.0f;

	glClearDepth(1.0);
	// glDepthFunc(GL_LEQUAL);
	// glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0f, 640.f/480.f, near_plane, far_plane);

    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);


    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, environment_color);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    float light_radius = 0.05f;

    for (int i = 0; i < 1; i++)
    {
        glEnable(GL_LIGHT0 + i);
        glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, light_diffuse[i]);
        //glLightf(GL_LIGHT0 + i, GL_LINEAR_ATTENUATION, 2.0f / light_radius);
        //glLightf(GL_LIGHT0 + i, GL_QUADRATIC_ATTENUATION, 1.0f / (light_radius * light_radius));
    }

    GLfloat mat_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);

    // glFogf(GL_FOG_START, 5);
    // glFogf(GL_FOG_END, 20);
    // glFogfv(GL_FOG_COLOR, environment_color);
    // Set some global render modes that we want to apply to all models
    
    glEnable(GL_NORMALIZE);
    //glEnable(GL_LIGHTING);
    // glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);
    // glDisable(GL_CULL_FACE);

    //font_init();
}

void renderer_common_draw()
{
    t += 10.f * platform_delta_seconds();
    //t+= 0.016;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    set_camera_transform(&camera);

    // TEST CUBE FOR COMMON DRAWING TEST

    float size = 1.0f;

    glPushMatrix();
        glTranslatef(0, 0, 3);
        glRotatef(0, 1, 1, 1);

        glBegin(GL_TRIANGLES);

            glColor3f(1.f, .0f, 1.0f);

            // Front face (Z+)
            glVertex3f(-size, -size,  size);
            glVertex3f( size, -size,  size);
            glVertex3f( size,  size,  size);

            glVertex3f(-size, -size,  size);
            glVertex3f( size,  size,  size);
            glVertex3f(-size,  size,  size);

            glColor3f(0.0f, 1.0f, 1.0f);

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

            glColor3f(1.0f, 1.0f, 1.0f);

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
    glPopMatrix();
    
    // glDisable(GL_LIGHTING);

    // ---- 2D UI OVERLAY ----
    // Save current matrices
    // glMatrixMode(GL_PROJECTION);
    // glPushMatrix();
    // glLoadIdentity();
    // glOrtho(0, 640, 480, 0, -1, 1); // pixel coords, top-left origin

    // glMatrixMode(GL_MODELVIEW);
    // glPushMatrix();
    // glLoadIdentity();

    // UI state (no depth; optional blending)
    // glDisable(GL_DEPTH_TEST);
    // glEnable(GL_BLEND); 
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // float quad_w, quad_h, 
    //       quad_x, quad_y, 
    //       quad_r, quad_g, quad_b, quad_a;

    // quad_w = 85.f; quad_h = 45.f;
    // quad_x = 250.f; quad_y = 100.0f;
    // quad_r = 0.2f; quad_g = 0.6f; quad_b = 0.9f; quad_a = 0.3f;

    // Not implemented fully yet for all platforms
    // MousePosition* m_pos = get_mouse_pos();

    // Check hover in the x direction
    //bool hover = (m_pos->x >= quad_x) && (m_pos->x <= (quad_x + quad_w));

    // Check hover in the y direction
    //hover = hover && (m_pos->y >= quad_y && m_pos->y <= (quad_y + quad_h));
    
    // if (hover)
    // {
    //     quad_a = 0.5f;
    // }

    // draw_quad(quad_x, quad_y,
    //           quad_w, quad_h,
    //           quad_r, quad_g, quad_b, quad_a); 

    //GLint text_padding = 10;

    // glColor4f(1.f, 0.f, 0.f, 1.f);
    
    // Not implemented for Dreamcast yet
    // font_print_string("hello world", 15 + text_padding, 125);
    
    // glDisable(GL_BLEND);

    // Restore
    // glMatrixMode(GL_MODELVIEW);  glPopMatrix();
    // glMatrixMode(GL_PROJECTION); glPopMatrix();
}
