#include "Buffer.h"
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
Buffer::Buffer(const char* inputName) {
	attribute_name = inputName;
	glGenBuffers(1, &vbo_data);
}

/** Call this function on each attribute_name of buffer
 **/
Buffer::~Buffer() {
	glDeleteBuffers(1, &vbo_data);
}

/** Call this procedure only once for one of these attribute_name :
 * 		elements, coord3d, texcoord
 * 	Call this procedure after procedure render while on loop procedure
 **/
void Buffer::draw() {
	if (attribute_name == "elements" || attribute_name == "coord3d" || attribute_name == "texcoord") {
		int size;
		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
		glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	}
}

/** Call this procedure only once for one of these attribute_name :
 * 		particles_coord3d, particles_position, particles_color
 * 	Call this procedure after procedure render while on loop procedure
 **/
void Buffer::draw(int rendered_count) {
	if (attribute_name == "particles_coord3d" || attribute_name == "particles_position" || attribute_name == "particles_color") {
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, rendered_count);
	}
}

/** Call this function on each attribute_name of buffer except for elements
 **/
bool Buffer::linkProgram(GLuint program) {
	if (attribute_name == "elements") {
		return (true);
	} else {
		attribute_coord = glGetAttribLocation(program, attribute_name);
		if (attribute_coord == -1) {
			std::cerr << "Could not bind attribute " << attribute_name << std::endl;
			return (false);
		} else {
			return (true);
		}
	}
}

/** Call this function for coord3d, texcoord, elements and particles_coord3d
 *	Call this procedure while on loop procedure
 **/
void Buffer::render() {
	int numberOfElements;
	if (attribute_name == "coord3d" || attribute_name == "texcoord") {
		glEnableVertexAttribArray(attribute_coord);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_data);
		if (attribute_name == "coord3d") {
			numberOfElements = 3;
		} else if (attribute_name == "texcoord") {
			numberOfElements = 2;
		}
		glVertexAttribPointer(
			attribute_coord, 	// attribute
			numberOfElements,   // number of elements per vertex, here (x,y)
			GL_FLOAT,           // the type of each element
			GL_FALSE,           // take our values as-is
			0,                  // no extra data between each position
			0                   // offset of first element
		);
	} else if (attribute_name == "elements") {
		/* Push each element in buffer_vertices to the vertex shader */
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_data);
	} else if (attribute_name == "particles_coord3d") {
		glEnableVertexAttribArray(attribute_coord);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_data);
		glVertexAttribPointer(
			attribute_coord, // attribute. No particular reason for 0, but must match the layout in the shader.
			3, // size
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			0, // stride
			(void*)0 // array buffer offset
		);
		glVertexAttribDivisor(attribute_coord, 0);
	}
}

/** Call this function on particles_position only
 *	Call this procedure after recalculating position data for particles while on loop procedure
 **/
void Buffer::render(GLfloat object_data[], int rendered_count, int max_count) {
	if (attribute_name == "particles_position") {
		glBindBuffer(GL_ARRAY_BUFFER, vbo_data);
		glBufferData(GL_ARRAY_BUFFER, max_count * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
		glBufferSubData(GL_ARRAY_BUFFER, 0, rendered_count * sizeof(GLfloat) * 4, object_data);

		glEnableVertexAttribArray(attribute_coord);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_data);
		glVertexAttribPointer(
			attribute_coord, // attribute. No particular reason for 1, but must match the layout in the shader.
			4, // size : x + y + z + size => 4
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			0, // stride
			(void*)0 // array buffer offset
		);
		glVertexAttribDivisor(attribute_coord, 1);
	}
}

/** Call this function on particles_color only
 *	Call this procedure after recalculating position data for particles while on loop procedure
 **/
void Buffer::render(GLubyte object_data[], int rendered_count, int max_count) {
	if (attribute_name == "particles_color") {
		glBindBuffer(GL_ARRAY_BUFFER, vbo_data);
		glBufferData(GL_ARRAY_BUFFER, max_count * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
		glBufferSubData(GL_ARRAY_BUFFER, 0, rendered_count * sizeof(GLubyte) * 4, object_data);

		glEnableVertexAttribArray(attribute_coord);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_data);
		glVertexAttribPointer(
			attribute_coord, // attribute. No particular reason for 1, but must match the layout in the shader.
			4, // size : r + g + b + a => 4
			GL_UNSIGNED_BYTE, // type
			GL_TRUE, // normalized? *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
			0, // stride
			(void*)0 // array buffer offset
		);
		glVertexAttribDivisor(attribute_coord, 1);
	}
}

/** Call this function on each attribute_name of buffer except elements
 *	Call this procedure after draw procedure while on loop procedure
 **/
void Buffer::renderClean() {
	if (attribute_name != "elements") {
		glDisableVertexAttribArray(attribute_coord);
	}
}

/** Call this function on each attribute_name of buffer except elements
 *	Call this procedure after constructor
 **/
void Buffer::setBufferData(GLfloat object_data[]) {
	if (attribute_name == "coord3d") {
		glBindBuffer(GL_ARRAY_BUFFER, vbo_data);
		glBufferData(GL_ARRAY_BUFFER, sizeof(object_data), object_data, GL_STATIC_DRAW);
	} else if (attribute_name == "texcoord") {
		for (int i = 1; i < 12; i++) {
			memcpy(&object_data[i*4*2], &object_data[0], 2*4*sizeof(GLfloat));
		}
		glBindBuffer(GL_ARRAY_BUFFER, vbo_data);
		glBufferData(GL_ARRAY_BUFFER, sizeof(object_data), object_data, GL_STATIC_DRAW);
	} else if (attribute_name == "particles_coord3d") {
		glBindBuffer(GL_ARRAY_BUFFER, vbo_data);
		glBufferData(GL_ARRAY_BUFFER, sizeof(object_data), object_data, GL_STATIC_DRAW);
	}
}

/** Call this function for attribute_name = "elements"
 *	Call this procedure after constructor
 **/
void Buffer::setBufferData(GLushort object_data[]) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_data);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(object_data), object_data, GL_STATIC_DRAW);
}

/** Call this function for attribute_name particles_position and particles_color
 *	Call this procedure after constructor
 **/
void Buffer::setBufferData(int max_count) {
	if (attribute_name == "particles_position") {
		glBindBuffer(GL_ARRAY_BUFFER, vbo_data);
		// Initialize with empty (NULL) buffer : it will be updated later, each frame.
		glBufferData(GL_ARRAY_BUFFER, max_count * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
	} else if (attribute_name == "particles_color") {
		glBindBuffer(GL_ARRAY_BUFFER, vbo_data);
		// Initialize with empty (NULL) buffer : it will be updated later, each frame.
		glBufferData(GL_ARRAY_BUFFER, max_count * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
	}
}