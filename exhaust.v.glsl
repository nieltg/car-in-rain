#version 140

attribute vec3 coord3d;

uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform uint time;

varying vec2 f_texcoord;


void main (void) {
  float time2 = time;
  float time1 = time2 / 10000.0;

  float frame = 0.1 + mod(coord3d.z - 0.5 + time1, 1.5);

  vec3 pos;
  pos.x = -coord3d.x / sqrt(frame);
  pos.y = coord3d.x * frame;
  pos.z = coord3d.y * frame;

  int id = gl_VertexID & 3;
  switch (id) {
    case 0:
      f_texcoord = vec2(0.0, 0.0);
      break;
    case 1:
      pos += vec3(0.3, 0.0, 0.0);
      f_texcoord = vec2(1.0, 0.0);
      break;
    case 2:
      pos += vec3(0.3, 0.3, 0.0);
      f_texcoord = vec2(1.0, 1.0);
      break;
    case 3:
      pos += vec3(0.0, 0.3, 0.0);
      f_texcoord = vec2(0.0, 1.0);
      break;
  }

  mat4 mvp = p * v * m;
  gl_Position = mvp * vec4(pos, 1.0);
}