#version 140

/**
 * From the OpenGL Programming wikibook: http://en.wikibooks.org/wiki/OpenGL_Programming
 * This file is in the public domain.
 * Contributors: Martin Kraus, Sylvain Beucler
 */

attribute vec3 v_coord;
attribute vec3 v_normal;
attribute vec2 texcoord;
// position of the vertex (and fragment) in world space
varying vec4 position;
// surface normal vector in world space
varying vec3 varyingNormalDirection;
varying vec2 f_texcoord;
uniform mat4 m, v, p;
uniform mat3 m_3x3_inv_transp;

void main () {
  position = m * vec4(v_coord, 1.0);
  varyingNormalDirection = normalize(m_3x3_inv_transp * v_normal);
  f_texcoord = texcoord;
  mat4 mvp = p * v * m;
  gl_Position = mvp * vec4(v_coord, 1.0);
}
