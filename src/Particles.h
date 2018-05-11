#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <GL/glew.h>

class Particles {
	private :
		const char* attribute_name;
		
	public :
		Particles(const char* inputName);
		~Particles();
};