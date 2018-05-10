#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <GL/glew.h>

class Texture {
	private :
		GLuint texture_id;

	public :
		Texture();
		~Texture();
		bool load(const char* path);
};