#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glbinding/gl/gl.h>
//#include <GL/glew.h>

#include <glbinding/gl/gl.h>
#include <globjects/base/File.h>
#include <globjects/base/StringTemplate.h>
#include <globjects/Program.h>
#include <globjects/VertexArray.h>
#include <globjects/Texture.h>
#include <globjects/VertexAttributeBinding.h>
#include <globjects/Buffer.h>
#include <globjects/Shader.h>

#include "Particle.h"
//#include "Buffer.h"

class ParticleContainer {
	private :
		int MAX_PARTICLES = 100000;
		int LastUsedParticle = 0;
		Particle* containerP;
		gl::GLfloat* position_size_data;
		gl::GLubyte* color_data;
		std::unique_ptr<globjects::Buffer> buffer_coord;
		std::unique_ptr<globjects::Buffer> buffer_position;
		std::unique_ptr<globjects::Buffer> buffer_color;
		std::unique_ptr<globjects::Program> program;
		gl::GLint attr_coord;
		gl::GLint attr_pos;
		gl::GLint uniform_mvp;
		gl::GLint attr_color;
		
	public :
		ParticleContainer();
		ParticleContainer(int maxCountSize);
		~ParticleContainer();
		void createProgram();
		void linkProgram(gl::GLfloat coord3d_input[]);
		void drawParticles(int particlesCount);
		int findUnusedParticle();
		int getMaxParticles();
		void setPositionData(int ParticlesCount, gl::GLfloat x, gl::GLfloat y, gl::GLfloat z, gl::GLfloat size);
		void setColorData(int ParticlesCount, gl::GLubyte r, gl::GLubyte g, gl::GLubyte b, gl::GLubyte a);
		void simulateParticles(double deltaTime, glm::vec3 cameraPosition);
		void sortParticles();
		ParticleContainer& operator=(const ParticleContainer& other);
};