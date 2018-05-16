#version 140

attribute vec3 coord3d;

uniform mat4 mvp;
uniform uint time;

void main (void) {
  vec3 pos = coord3d;

  float time1 = time;
  pos.y = mod(pos.y - (time1 / 500.0), 4);

  if ((gl_VertexID & 1) == 0) {
    pos.y += 0.1;
  }

  pos.y -= 1.5;

  gl_Position = mvp * vec4(pos, 1.0);
}
