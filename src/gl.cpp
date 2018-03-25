#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>

void init (void) {
}

void resize (int width, int height) {
    if (height == 0) ++height;

    float ratio = 1.0f * width / height;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluPerspective(45, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

void render (void) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glPointSize(1000);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    unsigned int tick = SDL_GetTicks();

    glLoadIdentity();
    //glRotatef(tick % 3600 * 0.1f, 0.0, 0.0, 1.0);
    houses();
    sky();
    road();
    car();
    /*glBegin(GL_TRIANGLES);
    glColor3f ( 1.0,1.0,0.0);
    glVertex3f(-0.2,0.2, -3.0);
    glColor3f ( 1.0,0.0,0.0);
    glVertex3f(-0.2, -0.2, -3.0);
    glColor3f ( 0.0,1.0,0.0);
    glVertex3f( 0.2,0.2, -3.0);

    glColor3f ( 1.0,1.0,1.0);
    glVertex3f( -0.4,-0.6, -3.0);
    glColor3f ( 1.0,1.0,1.0);
    glVertex3f( -0.4, -0.4, -3.0);
    glColor3f ( 1.0,1.0,1.0);
    glVertex3f( -0.6,-0.6, -3.0);
    glEnd();*/
}

void houses(void) {
    GLfloat vertices1[]= {
         0.0,300.0,0.0,
         0.0,320.0,0.0,
        20.0,330.0,0.0,
        20.0,340.0,0.0,
        40.0,340.0,0.0,
        40.0,310.0,0.0,
        60.0,310.0,0.0,
        60.0,300.0,0.0
    }
    glPushMatrix();
        glTranslatef(-1,0,0);
        glBegin(GL_POLYGON);
            for (int i=0; i<8; i++) {
                glVertex3f(vertices1[i*3],vertices[(i*3)+1],vertices[(i*3)+2]);
                glColor3f(1.0,1.0,0.0);
            }
        glEnd();
    glPopMatrix();
}

void sky(void) {
    GLfloat vertices1[]= {
            0.0, 300.0,-1.0,
            0.0,1000.0,-1.0,
         1000.0,1000.0,-1.0,
         1000.0, 300.0,-1.0
    }
    glPushMatrix();
        glBegin(GL_POLYGON);
            for (int i=0; i<4; i++) {
                glVertex3f(vertices1[i*3],vertices[(i*3)+1],vertices[(i*3)+2]);
                glColor3f(0.0,0.0,1.0);
            }
        glEnd();
    glPopMatrix();
}

void road (void) {
    GLfloat vertices1[]= {
            0.0,   0.0,-1.0,
            0.0, 300.0,-1.0,
         1000.0, 300.0,-1.0,
         1000.0,   0.0,-1.0
    }
    glPushMatrix();
        glBegin(GL_POLYGON);
            for (int i=0; i<4; i++) {
                glVertex3f(vertices1[i*3],vertices[(i*3)+1],vertices[(i*3)+2]);
                glColor3f(0.5,0.5,0.5);
            }
        glEnd();
    glPopMatrix();
}

void car(void) {
    GLfloat vertices1[]= {
        100.0, 150.0, 1.0,
        100.0, 500.0, 1.0,
        300.0, 500.0, 1.0,
        300.0, 700.0, 1.0,
        600.0, 700.0, 1.0,
        600.0, 500.0, 1.0,
        900.0, 500.0, 1.0,
        900.0, 150.0, 1.0,
    }
    glPushMatrix();
        glBegin(GL_POLYGON);
            for (int i=0; i<8; i++) {
                glVertex3f(vertices1[i*3],vertices[(i*3)+1],vertices[(i*3)+2]);
                glColor3f(0.0,1.0,0.0);
            }
        glEnd();
        tires();
    glPopMatrix();
}

void tires(void) {

}