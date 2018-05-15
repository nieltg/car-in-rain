attribute vec3 coord3d;
attribute vec2 texcoord;
attribute vec3 norm;
varying vec2 f_texcoord;
uniform sampler2D mytexture;

struct lightSource
{
  vec4 position;
  vec4 diffuse;
  vec4 specular;
  float constantAttenuation, linearAttenuation, quadraticAttenuation;
  float spotCutoff, spotExponent;
  vec3 spotDirection;
};

struct material
{
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  float shininess;
};

void main(void) {
  lightSource light0 = lightSource(
    vec4(0.0,  1.0,  2.0, 1.0),
    vec4(1.0,  1.0,  1.0, 1.0),
    vec4(1.0,  1.0,  1.0, 1.0),
    0.0, 1.0, 0.0,
    180.0, 0.0,
    vec3(0.0, 0.0, 0.0)
  );
  material mymaterial = material(
    vec4(0.2, 0.2, 0.2, 1.0),
    vec4(1.0, 0.8, 0.8, 1.0),
    vec4(1.0, 1.0, 1.0, 1.0),
    5.0
  );

  vec2 flipped_texcoord = vec2(f_texcoord.x, 1.0 - f_texcoord.y);
  vec4 texture = texture2D(mytexture, flipped_texcoord);

  gl_FragColor = texture;
}
