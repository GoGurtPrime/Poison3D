// renderer_kos.c  (GLdc path)
#include "renderer.h"
#include "../core/camera.h"

#include <kos.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glkos.h>
#include <math.h>

static float t = 0.f;
static camera_t camera;
static const GLfloat clear_col[4] = {0.1f, 0.03f, 0.2f, 1.f};

void renderer_init(int width, int height) {
    camera.distance = -10.0f;
    camera.rotation = 0.0f;

    glKosInit();
    glMatrixMode(GL_PROJECTION);
    
    float aspect_ratio = (float)width / (float)height;
    float near_plane = 1.0f;
    float far_plane = 50.0f;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-near_plane*aspect_ratio, near_plane*aspect_ratio, -near_plane, near_plane, near_plane, far_plane);

    camera_transform(&camera);     // should translate Z by -10 for your setup

    //gluPerspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    // 🔑 for flat color
    glDisable(GL_TEXTURE_2D);

    // Sensible defaults
    //glEnable(GL_DEPTH_TEST);
    // glDisable(GL_CULL_FACE);      // turn back on after verifying geometry
    glShadeModel(GL_SMOOTH);

    /* Expect CW verts */
    //glFrontFace(GL_CW);

    /* Set Blend Mode */
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLfloat mat_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);
}

void renderer_render(void) {
    t += 0.016f;

    glClearColor(0.1f, 0.03f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glMatrixMode(GL_MODELVIEW);
    //camera_transform(&camera);     // should translate Z by -10 for your setup

    glPushMatrix();
    glRotatef(sinf(t) * 45.0f, 0.0f, 0.0f, 1.0f);

    float size = 0.2f;

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

    glPopMatrix();

    glKosSwapBuffers();            // GLdc flush/swap
}

void renderer_shutdown(void) {}
