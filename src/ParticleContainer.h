#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <GL/glew.h>
#include "Particle.h"

class ParticleContainer {
	private :
		int MAX_PARTICLES = 100000;
		int LastUsedParticle = 0;
		Particle* containerP;
		
	public :
		ParticleContainer();
		ParticleContainer(int maxCountSize);
		~ParticleContainer();
		int findUnusedParticle();
		int getMaxParticles();
		void simulateParticles();
		void sortParticles();
};