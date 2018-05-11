#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <GL/glew.h>

class Buffer {
	private :
		const char* attribute_name;
		GLuint vbo_data;
		GLint attribute_coord;
		
	public :
		Buffer(const char* inputName);
		~Buffer();
		bool linkProgram(GLuint program);
		void setBufferData(GLfloat object_data[]);
		void setBufferData(GLushort object_data[]);
		void render();
		void renderClean();
};