#version 140

varying vec2 f_texcoord;
varying float f_alpha;

uniform sampler2D texture;


void main (void) {
  vec4 col = texture2D(texture, f_texcoord);
  col.a *= f_alpha;

  gl_FragColor = col;
}
