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
//#include "OBJ_Loader.h"
//#include "Buffer.h"

class ParticleContainer {
	private :
		int MAX_PARTICLES = 100000;
		int LastUsedParticle = 0;

		Particle* containerP;
		gl::GLfloat* position_size_data;
		gl::GLubyte* color_data;

		std::unique_ptr<globjects::VertexArray> m_vao;
		std::unique_ptr<globjects::Buffer> m_vertices;
		std::unique_ptr<globjects::Buffer> m_texcoord;
		std::unique_ptr<globjects::Buffer> m_indices;

		std::unique_ptr<globjects::Texture> m_texture;

		gl::GLint attr_coord;
		gl::GLint attr_texcoord;
		gl::GLint attr_pos;
		gl::GLint attr_color;
		gl::GLint uniform_mvp;
		gl::GLint uniform_tex;

		std::unique_ptr<globjects::Buffer> buffer_coord;
		std::unique_ptr<globjects::Buffer> buffer_position;
		std::unique_ptr<globjects::Buffer> buffer_color;
		
		std::unique_ptr<globjects::Program> program;
		std::unique_ptr<globjects::File> g_vertexShaderSource;
		std::unique_ptr<globjects::AbstractStringSource> g_vertexShaderTemplate;
		std::unique_ptr<globjects::Shader> g_vertexShader;
		std::unique_ptr<globjects::File> g_fragmentShaderSource;
		std::unique_ptr<globjects::AbstractStringSource> g_fragmentShaderTemplate;
		std::unique_ptr<globjects::Shader> g_fragmentShader;

		size_t indices_len;
		
	public :
		ParticleContainer();
		ParticleContainer(int maxCountSize);
		~ParticleContainer();
		void createProgram();
		void linkBuffer(std::vector<glm::vec3> vertices, std::vector<glm::vec2> texcoord, std::vector<gl::GLuint> indices, size_t indices_size);
		void drawParticles(int particlesCount, glm::mat4 mvp);
		int findUnusedParticle();
		int getMaxParticles();
		void setPositionData(int ParticlesCount, gl::GLfloat x, gl::GLfloat y, gl::GLfloat z, gl::GLfloat size);
		void setColorData(int ParticlesCount, gl::GLubyte r, gl::GLubyte g, gl::GLubyte b, gl::GLubyte a);
		void simulateParticles(double deltaTime, glm::vec3 cameraPosition);
		void sortParticles();
		void setTexture();
		//void loadObj();
		ParticleContainer& operator=(const ParticleContainer& other);
};