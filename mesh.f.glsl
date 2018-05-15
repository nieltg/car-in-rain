varying vec3 f_coord3d;
varying vec2 f_texcoord;
varying vec3 f_norm;
uniform sampler2D mytexture;
uniform mat4 m, v, p;
uniform mat4 v_inv;

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

  //create specific lights and materials for this shader
  lightSource light0 = lightSource(
    vec4(0.0,  1.0,  2.0, 1.0),
    vec4(1.0,  1.0,  1.0, 1.0),
    vec4(1.0,  1.0,  1.0, 1.0),
    0.0, 1.0, 0.0,
    180.0, 0.0,
    vec3(0.0, 0.0, 0.0)
  );
  material myMaterial = material(
    vec4(0.2, 0.2, 0.2, 1.0),
    vec4(1.0, 0.8, 0.8, 1.0),
    vec4(1.0, 1.0, 1.0, 1.0),
    512.0
  );

  vec3 normalDirection = normalize(f_norm);
  vec3 viewDirection = normalize(vec3(v_inv * vec4(0.0, 0.0, 0.0, 1.0) - f_coord3d));
  vec3 lightDirection;
  float attenuation;

  //initialize total lighting with ambient lighting
  vec4 scene_ambient = vec4(0.2, 0.2, 0.2, 1.0);
  vec3 totalLighting = vec3(scene_ambient) * vec3(myMaterial.ambient);

  if (light0.position.w == 0.0) //directional light?
  {
    attenuation = 1.0;
    lightDirection = normalize(vec3(light0.position));
  }
  else
  {
    vec3 positionToLightSource = vec3(light0.position - f_coord3d);
    float distance = length(positionToLightSource);
    lightDirection = normalize(positionToLightSource); 
	  attenuation = 1.0 / (light0.constantAttenuation
			       + light0.linearAttenuation * distance
			       + light0.quadraticAttenuation * distance * distance);

    if (light0.spotCutoff <= 90.0) //spotlight?
    {
      float clampedCosine = max(0.0, dot(-lightDirection, normalize(light0.spotDirection)));
	    if (clampedCosine < cos(radians(light0.spotCutoff))) // outside of spotlight cone?
      {
        attenuation = 0.0;
      }
      else
      {
        attenuation += pow(clampedCosine, light0.spotExponent);
      }
    }
  }
  
  vec3 diffuseReflection = attenuation 
	  * vec3(light0.diffuse) * vec3(myMaterial.diffuse)
	  * max(0.0, dot(normalDirection, lightDirection));
  vec3 specularReflection;
  if (dot(normalDirection, lightDirection) < 0.0) // light source on the wrong side?
  {
    specularReflection = vec3(0.0, 0.0, 0.0); // no specular reflection
  }
  else
  {
    specularReflection = attenuation * vec3(light0.specular) * vec3(myMaterial.specular)
	    * pow(max(0.0, dot(reflect(-lightDirection, normalDirection), viewDirection)), myMaterial.shininess);
  }

  totalLighting += diffuseReflection + specularReflection;

  vec4 finalLighting = vec4(totalLighting, 1.0);

  vec2 flipped_texcoord = vec2(f_texcoord.x, 1.0 - f_texcoord.y);
  vec4 texture = texture2D(mytexture, flipped_texcoord);

  gl_FragColor = texture * finalLighting;
}
