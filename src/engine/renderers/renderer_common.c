#include "renderer_common.h"
#include "../core/camera.h"
#include "../../platforms/platform.h"
#include "../core/gl.h"

#include <math.h>

// Current time (just using for testing temporarily)
static float t = 0.f;

// Used by GL Clear Color
static const GLfloat environment_color[] = {0.03f, 0.03f, 0.03f, 1.f};

static camera_t camera;

void renderer_common_setup(int width, int height)
{
    camera.position[0] = 0.f;
    camera.position[1] = 0.f;
    camera.position[2] = -10.f;

    camera.rotation[0] = 0.f;
    camera.rotation[1] = 60.f;
    camera.rotation[2] = 0.f;

    glClearColor(0.f, 0.f, 0.3f, 1.f);

    float near_plane = 0.1f;
    float far_plane = 60.f;

	glClearDepth(1.0);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // TODO: Replace Aspect Ratio with the actual aspect ratio
    gluPerspective(60.f, 640.f/480.f, near_plane, far_plane);

    glMatrixMode(GL_MODELVIEW);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, environment_color);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    GLfloat mat_diffuse[] = {1.f, 1.f, 1.f, 1.f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);

    glEnable(GL_NORMALIZE);
}

void renderer_common_draw()
{
    t += platform_delta_seconds();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    set_camera_transform(&camera);

    float cube_size = 1.f;

    glPushMatrix();
        glTranslatef(0.f, 0.f, 3.f);
        glRotatef(0.f, 1.f, 1.f, 1.f);

        // TEST CUBE FOR COMMON DRAWING TEST
        glBegin(GL_TRIANGLES);
            glColor3f(1.f, .0f, 1.f);

            // Front face (Z+)
            glVertex3f(-cube_size, -cube_size,  cube_size);
            glVertex3f( cube_size, -cube_size,  cube_size);
            glVertex3f( cube_size,  cube_size,  cube_size);

            glVertex3f(-cube_size, -cube_size,  cube_size);
            glVertex3f( cube_size,  cube_size,  cube_size);
            glVertex3f(-cube_size,  cube_size,  cube_size);

            glColor3f(0.f, 1.f, 1.f);

            // Back face (Z-)
            glVertex3f( cube_size, -cube_size, -cube_size);
            glVertex3f(-cube_size, -cube_size, -cube_size);
            glVertex3f(-cube_size,  cube_size, -cube_size);

            glVertex3f( cube_size, -cube_size, -cube_size);
            glVertex3f(-cube_size,  cube_size, -cube_size);
            glVertex3f( cube_size,  cube_size, -cube_size);

            glColor3f(0.f, 0.f, 1.f);

            // Left face (X-)
            glVertex3f(-cube_size, -cube_size, -cube_size);
            glVertex3f(-cube_size, -cube_size,  cube_size);
            glVertex3f(-cube_size,  cube_size,  cube_size);

            glVertex3f(-cube_size, -cube_size, -cube_size);
            glVertex3f(-cube_size,  cube_size,  cube_size);
            glVertex3f(-cube_size,  cube_size, -cube_size);

            glColor3f(1.f, 1.f, 1.f);

            // Right face (X+)
            glVertex3f( cube_size, -cube_size,  cube_size);
            glVertex3f( cube_size, -cube_size, -cube_size);
            glVertex3f( cube_size,  cube_size, -cube_size);

            glVertex3f( cube_size, -cube_size,  cube_size);
            glVertex3f( cube_size,  cube_size, -cube_size);
            glVertex3f( cube_size,  cube_size,  cube_size);

            glColor3f(1.f, 0.f, 1.f);

            // Top face (Y+)
            glVertex3f(-cube_size,  cube_size,  cube_size);
            glVertex3f( cube_size,  cube_size,  cube_size);
            glVertex3f( cube_size,  cube_size, -cube_size);

            glVertex3f(-cube_size,  cube_size,  cube_size);
            glVertex3f( cube_size,  cube_size, -cube_size);
            glVertex3f(-cube_size,  cube_size, -cube_size);

            glColor3f(1.f, 1.f, 1.f);

            // Bottom face (Y-)
            glVertex3f(-cube_size, -cube_size, -cube_size);
            glVertex3f( cube_size, -cube_size, -cube_size);
            glVertex3f( cube_size, -cube_size,  cube_size);

            glVertex3f(-cube_size, -cube_size, -cube_size);
            glVertex3f( cube_size, -cube_size,  cube_size);
            glVertex3f(-cube_size, -cube_size,  cube_size);    
        glEnd();
    glPopMatrix();
}
