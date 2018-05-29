#version 140

attribute vec3 coord3d;

uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform uint time;

varying vec2 f_texcoord;
varying float f_alpha;


void main (void) {
  float time2 = time;
  float time1 = time2 / 5000.0;

  float frame = 0.1 + mod(coord3d.z - 0.5 + time1, 1.5);

  vec3 center;
  center.z = -5.5 + coord3d.x / sqrt(frame);
  center.y = coord3d.x * frame;
  center.x = coord3d.y * frame;

  f_alpha = 1.5 - frame;

  vec3 cam_r = vec3(v[0][0], v[1][0], v[2][0]);
  vec3 cam_u = vec3(v[0][1], v[1][1], v[2][1]);

  float size = 0.5 * frame;

  vec3 pos;

  int id = gl_VertexID & 0x3;
  switch (id) {
    case 0:
      pos = center - (cam_r + cam_u) * size;
      f_texcoord = vec2(0.0, 0.0);
      break;
    case 1:
      pos = center - (cam_r - cam_u) * size;
      f_texcoord = vec2(1.0, 0.0);
      break;
    case 2:
      pos = center + (cam_r + cam_u) * size;
      f_texcoord = vec2(1.0, 1.0);
      break;
    case 3:
      pos = center + (cam_r - cam_u) * size;
      f_texcoord = vec2(0.0, 1.0);
      break;
  }

  mat4 vp = p * v;
  gl_Position = vp * vec4(pos, 1.0);
}
