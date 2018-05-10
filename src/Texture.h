#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <GL/glew.h>

class Texture {
	private :
		GLuint texture_id;
		GLint uniform_mytexture;

	public :
		Texture();
		~Texture();
		bool linkProgram(GLuint program);
		bool load(const char* path);
		void render();
};