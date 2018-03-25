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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    unsigned int tick = SDL_GetTicks();

    glLoadIdentity();
    //glRotatef(tick % 3600 * 0.1f, 0.0, 0.0, 1.0);

    glBegin(GL_TRIANGLES);
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
    glEnd();
    
    glColor3f(0.3f,0.3f,0.3f);
    
    glBegin(GL_POLYGON);
      glVertex3f(-1.0f,-1.0f,-3.0);
      glVertex3f(1.0f,-1.0f,-3.0);
      glVertex3f(1.0f,-0.5f,-3.0);
      glVertex3f(-1.0f,-0.5f,-3.0);
    glEnd();
}

void houses(void) {
    glBegin(GL_POLYGON);
    glEnd();
}

void sky(void) {

}

void road (void) {

}

void car(void) {

}

void tires(void) {

}