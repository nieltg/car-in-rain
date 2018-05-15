attribute vec3 coord3d;
attribute vec2 texcoord;
attribute vec3 norm;
varying vec3 f_coord3d;
varying vec2 f_texcoord;
varying vec3 f_norm;
uniform mat4 mvp;
uniform mat4 m, v, p;
uniform mat4 v_inv;


void main(void) {
  gl_Position = mvp * vec4(coord3d, 1.0);
  f_texcoord = texcoord;
  //pass attribute to fragment shader
  f_coord3d = coord3d;
  f_norm = norm;
}
