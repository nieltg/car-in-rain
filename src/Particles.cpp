#include "particles.h"
#include <iostream>

//vbo_cube vertices, vbo_cube_texcoords, ibo_cube_elements, particles_position, particles_color, particles_coord3d
//attribute_name coord3d, texcoord, elements, particles_position, particles_color, particles_coord3d

/**	Call this function on each attribute_name of buffer
 *	supported attribute_name :
 *		coord3d				: 
 *		texcoord			: 
 *		elements			:
 *		particles_position	:
 *		particles_color		:
 *		particles_coord3d	:
 **/
Particles::Particles(const char* inputName) {
	attribute_name = inputName;
}

/** Call this function on each attribute_name of buffer
 **/
Particles::~Particles() {
	
}