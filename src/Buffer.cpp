#include "buffer.h"
#include <iostream>

//vbo_cube vertices, vbo_cube_texcoords, ibo_cube_elements
//attribute_name coord3d, texcoord, elements
Buffer::Buffer(const char* inputName) {
	attribute_name = inputName;
	glGenBuffers(1, &vbo_data);
}

Buffer::~Buffer() {
	glDeleteBuffers(1, &vbo_data);
}

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
	} else {
		
	}
}

void Buffer::setBufferData(GLushort object_data[]) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_data);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(object_data), object_data, GL_STATIC_DRAW);
}

void Buffer::render() {
	int numberOfElements;
	if (attribute_name != "elements") {
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
	} else {
		int size;
		/* Push each element in buffer_vertices to the vertex shader */
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_data);
		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
		glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	}
}

//Call this function after render in each loop
void Buffer::renderClean() {
	if (attribute_name != "elements") {
		glDisableVertexAttribArray(attribute_coord);
	}
}