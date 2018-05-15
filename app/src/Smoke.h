#pragma once

#include <memory>

#include <glbinding/gl/gl.h>

#include <globjects/base/File.h>
#include <globjects/base/StringTemplate.h>
#include <globjects/Buffer.h>
#include <globjects/Program.h>
#include <globjects/Shader.h>
#include <globjects/Texture.h>
#include <globjects/VertexArray.h>

#include "Particle.h"

class Smoke {
	public:
		const int MAX_PARTICLES = 1000;
		Particle* containerP;

		Smoke (void);

		void draw (glm::mat4 _vp, glm::mat4 _v);

		int findUnusedParticle();
		void sortParticles();
		int simulateParticles(int deltaTime, glm::vec3 cameraPosition);
		void setPositionData(int ParticlesCount, gl::GLfloat x, gl::GLfloat y, gl::GLfloat z, gl::GLfloat size);
		void setColorData(int ParticlesCount, gl::GLubyte r, gl::GLubyte g, gl::GLubyte b, gl::GLubyte a);

	private:
		int LastUsedParticle;
		std::unique_ptr<globjects::Texture> texture;

		std::unique_ptr<globjects::Program> program;
		std::unique_ptr<globjects::File> shader_v_src;
		std::unique_ptr<globjects::AbstractStringSource> shader_v_preprocessed;
		std::unique_ptr<globjects::Shader> shader_v;
		std::unique_ptr<globjects::File> shader_f_src;
		std::unique_ptr<globjects::AbstractStringSource> shader_f_preprocessed;
		std::unique_ptr<globjects::Shader> shader_f;

		gl::GLuint CameraRight_worldspace_ID;
		gl::GLuint CameraUp_worldspace_ID;
		gl::GLuint ViewProjMatrixID;
		gl::GLuint TextureID;

		std::unique_ptr<globjects::VertexArray> vao;
		std::unique_ptr<globjects::Buffer> b_vertices;
		std::unique_ptr<globjects::Buffer> b_position;
		std::unique_ptr<globjects::Buffer> b_color;

		size_t draw_len;

		gl::GLfloat* position_size_data;
		gl::GLubyte* color_data;
};
