#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include "Particle.h"
#include "Buffer.h"

class ParticleContainer {
	private :
		int MAX_PARTICLES = 100000;
		int LastUsedParticle = 0;
		Particle* containerP;
		GLfloat* position_size_data;
		GLubyte* color_data;
		Buffer buffer_coord;
		Buffer buffer_position;
		Buffer buffer_color;
		
	public :
		ParticleContainer(int maxCountSize, GLfloat coord3d_data[], GLuint program);
		~ParticleContainer();
		void drawParticles(int particlesCount);
		int findUnusedParticle();
		int getMaxParticles();
		void setPositionData(int ParticlesCount, GLfloat x, GLfloat y, GLfloat z, GLfloat size);
		void setColorData(int ParticlesCount, GLubyte r, GLubyte g, GLubyte b, GLubyte a);
		void simulateParticles(double deltaTime, glm::vec3 cameraPosition);
		void sortParticles();
};