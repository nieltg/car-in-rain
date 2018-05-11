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
		void draw();
		void draw(int rendered_count);
		bool linkProgram(GLuint program);
		void render();
		void render(GLfloat object_data[], int rendered_count, int max_count);
		void render(GLubyte object_data[], int rendered_count, int max_count);
		void renderClean();
		void setBufferData(GLfloat object_data[]);
		void setBufferData(GLushort object_data[]);
		void setBufferData(int max_count);
};