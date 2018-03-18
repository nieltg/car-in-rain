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
  glRotatef(tick % 3600 * 0.1f, 0.0, 0.0, 1.0);

  glBegin(GL_TRIANGLE_STRIP);
  glColor3f ( 1.0,  1.0,  0.0);
  glVertex3f(-0.5,  0.5, -3.0);
  glColor3f ( 1.0,  0.0,  0.0);
  glVertex3f(-0.5, -0.5, -3.0);
  glColor3f ( 0.0,  1.0,  0.0);
  glVertex3f( 0.5,  0.5, -3.0);
  glColor3f ( 0.0,  0.0,  1.0);
  glVertex3f( 0.5, -0.5, -3.0);
  glEnd();
}
