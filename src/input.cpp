#include <GL/glut.h>

void onMouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    arcball_on = true;
    last_mx = cur_mx = x;
    last_my = cur_my = y;
  } else {
    arcball_on = false;
  }
}

void onSpecial(int key, int x, int y) {
  int modifiers = glutGetModifiers();
  if ((modifiers & GLUT_ACTIVE_ALT) == GLUT_ACTIVE_ALT)
    strife = 1;
  else
    strife = 0;

  if ((modifiers & GLUT_ACTIVE_SHIFT) == GLUT_ACTIVE_SHIFT)
    speed_factor = 0.1;
  else
    speed_factor = 1;

  switch (key) {
  case GLUT_KEY_F1:
    view_mode = MODE_OBJECT;
    break;
  case GLUT_KEY_F2:
    view_mode = MODE_CAMERA;
    break;
  case GLUT_KEY_F3:
    view_mode = MODE_LIGHT;
    break;
  case GLUT_KEY_LEFT:
    rotY_direction = 1;
    break;
  case GLUT_KEY_RIGHT:
    rotY_direction = -1;
    break;
  case GLUT_KEY_UP:
    transZ_direction = 1;
    break;
  case GLUT_KEY_DOWN:
    transZ_direction = -1;
    break;
  case GLUT_KEY_PAGE_UP:
    rotX_direction = -1;
    break;
  case GLUT_KEY_PAGE_DOWN:
    rotX_direction = 1;
    break;
  case GLUT_KEY_HOME:
    init_view();
    break;
  }
}

void onSpecialUp(int key, int x, int y) {
  switch (key) {
  case GLUT_KEY_LEFT:
  case GLUT_KEY_RIGHT:
    rotY_direction = 0;
    break;
  case GLUT_KEY_UP:
  case GLUT_KEY_DOWN:
    transZ_direction = 0;
    break;
  case GLUT_KEY_PAGE_UP:
  case GLUT_KEY_PAGE_DOWN:
    rotX_direction = 0;
    break;
  }
}
