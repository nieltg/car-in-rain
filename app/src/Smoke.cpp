#include <random>
#include <vector>
#include <iostream>
#include <algorithm>

#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <globjects/VertexAttributeBinding.h>

#include "Smoke.h"

Smoke::Smoke (void) {
	// Shaders.
	shader_v_src = globjects::Shader::sourceFromFile("misc/Particle.v.glsl");
	shader_v_preprocessed = globjects::Shader::applyGlobalReplacements(
	shader_v_src.get());
	shader_v = globjects::Shader::create(
	gl::GL_VERTEX_SHADER, shader_v_preprocessed.get());

	shader_f_src = globjects::Shader::sourceFromFile("misc/Particle.f.glsl");
	shader_f_preprocessed = globjects::Shader::applyGlobalReplacements(
	shader_f_src.get());
	shader_f = globjects::Shader::create(
	gl::GL_FRAGMENT_SHADER, shader_f_preprocessed.get());

	program = globjects::Program::create();
	program->attach(shader_v.get(), shader_f.get());

	CameraRight_worldspace_ID = program->getUniformLocation("CameraRight_worldspace");
	CameraUp_worldspace_ID = program->getUniformLocation("CameraUp_worldspace");
	ViewProjMatrixID = program->getUniformLocation("VP");

	TextureID = program->getUniformLocation("myTextureSampler");

	const gl::GLfloat vertex_buffer_data[] = { 
		 -0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		 -0.5f,0.5f, 0.0f,
		0.5f,0.5f, 0.0f,
	};

	vao = globjects::VertexArray::create();
	b_vertices = globjects::Buffer::create();
	b_vertices->setData(vertex_buffer_data, gl::GL_STATIC_DRAW);

	{
		auto vao_bind = vao->binding(0);
		//vao_bind->setAttribute(i_attr_coord3d);
		vao_bind->setBuffer(b_vertices.get(), 0, sizeof(glm::vec3));
		vao_bind->setFormat(sizeof(vertex_buffer_data), gl::GL_FLOAT, gl::GL_FALSE, 0);
		vao->enable(0);
	}

	gl::GLfloat* position_size_data = new gl::GLfloat[MAX_PARTICLES * 4];

	b_position = globjects::Buffer::create();
	b_position->setData(NULL, gl::GL_STREAM_DRAW);

	{
		auto vao_bind = vao->binding(1);
		//vao_bind->setAttribute(i_attr_coord3d);
		vao_bind->setBuffer(b_position.get(), 0, sizeof(glm::vec3));
		vao_bind->setFormat(sizeof(position_size_data), gl::GL_FLOAT*, gl::GL_FALSE, 0);
		vao->enable(0);
	}

	gl::GLubyte* color_data         = new gl::GLubyte[MAX_PARTICLES * 4];

	b_color = globjects::Buffer::create();
	b_color->setData(NULL, gl::GL_STREAM_DRAW);

	{
		auto vao_bind = vao->binding(2);
		//vao_bind->setAttribute(i_attr_coord3d);
		vao_bind->setBuffer(b_color.get(), 0, sizeof(glm::vec3));
		vao_bind->setFormat(sizeof(color_data), gl::GL_uByte*, gl::GL_FALSE, 0);
		vao->enable(0);
	}
	// Vertices.
	/*std::vector<glm::vec3> vertices;

	std::random_device rd;
	std::mt19937 generator(rd());

	std::uniform_real_distribution<> r(-5.0, 5.0);

	for (int i = 0; i < N_PARTICLE; ++i) {
		glm::vec3 pos = glm::vec3(r(generator), r(generator), r(generator));

		vertices.push_back(pos);
		vertices.push_back(pos);
	}

	vao = globjects::VertexArray::create();

	b_vertices = globjects::Buffer::create();
	b_vertices->setData(vertices, gl::GL_STATIC_DRAW);

	{
		auto vao_bind = vao->binding(0);
		vao_bind->setAttribute(i_attr_coord3d);
		vao_bind->setBuffer(b_vertices.get(), 0, sizeof(glm::vec3));
		vao_bind->setFormat(vertices.size(), gl::GL_FLOAT, gl::GL_FALSE, 0);
		vao->enable(0);
	}

	draw_len = vertices.size();*/

	// Texture.
	{
		auto res_texture = IMG_Load("misc/mesh.png");

		if (!res_texture) {
			throw std::runtime_error("Unable to load misc/mesh.png");
		}

		texture = globjects::Texture::create(gl::GL_TEXTURE_2D);
		texture->setParameter(gl::GL_TEXTURE_MIN_FILTER, gl::GL_LINEAR);
		texture->setParameter(gl::GL_TEXTURE_MAG_FILTER, gl::GL_LINEAR);
		texture->setParameter(gl::GL_TEXTURE_WRAP_S, gl::GL_CLAMP_TO_EDGE);
		texture->setParameter(gl::GL_TEXTURE_WRAP_T, gl::GL_CLAMP_TO_EDGE);

		texture->image2D(
			0,
			gl::GL_RGBA,
			glm::ivec2(res_texture->w, res_texture->h),
			0,
			gl::GL_RGBA,
			gl::GL_UNSIGNED_BYTE,
			res_texture->pixels);

		SDL_FreeSurface(res_texture);
	}
}

void Smoke::draw (glm::mat4 _vp, glm::mat4 _v) {
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0));
	glm::mat4 mvp = _vp * model;

	gl::glActiveTexture(gl::GL_TEXTURE0);
	texture->bind();

	program->use();
	program->setUniform(CameraRight_worldspace_ID, glm::vec3(_v[0][0],_v[1][0],_v[2][0]));
	program->setUniform(CameraUp_worldspace_ID, glm::vec3(_v[0][1],_v[1][1],_v[2][1]));
	program->setUniform(ViewProjMatrixID, &_vp[0][0]);
	//program->setUniform(i_uniform_time, SDL_GetTicks());
	int ParticlesCount = 2;
	vao->drawArraysInstanced(gl::GL_TRIANGLE_STRIP, 0, 4, ParticlesCount);
	program->release();

	texture->unbind();
}

void Smoke::setPositionData(int ParticlesCount, gl::GLfloat x, gl::GLfloat y, gl::GLfloat z, gl::GLfloat size) {

}
void Smoke::setColorData(int ParticlesCount, gl::GLubyte r, gl::GLubyte g, gl::GLubyte b, gl::GLubyte a) {

}

int Smoke::findUnusedParticle() {
	int i = LastUsedParticle;
	int result;
	while (i < MAX_PARTICLES && containerP[i].isAlive()) {
		i = i + 1;
	}
	if (i < MAX_PARTICLES && containerP[i].isDead()) {
		LastUsedParticle = i;
		result = i;
	} else {
		int i = 0;
		while (i < LastUsedParticle && containerP[i].isAlive()) {
			i = i + 1;
		}
		if (i < LastUsedParticle && containerP[i].isDead()) {
			LastUsedParticle = i;
			result = i;
		} else {
			result = 0;
		}
	}
	return (result);
}

void Smoke::sortParticles() {
	std::sort(&containerP[0], &containerP[MAX_PARTICLES]);
}

void Smoke::simulateParticles(int deltaTime, glm::vec3 cameraPosition) {
	int newparticles = (int)(deltaTime*10000.0);
	if (newparticles > (int)(0.016f*10000.0)) {
		newparticles = (int)(0.016f*10000.0);
	}

	for(int i=0; i<newparticles; i++) {
		int particleIndex = findUnusedParticle();
		containerP[particleIndex].revive(5,glm::vec3(0,0,-20),glm::vec3(0, 10, 0),1.5);
	}

	int particlesCount = 0;
	for(int i=0; i<MAX_PARTICLES; i++){
		if (containerP[i].isAlive()) {
			containerP[i].decreaseLife((float) deltaTime);
			if (containerP[i].isAlive()) {
				containerP[i].simulateGravity(deltaTime, cameraPosition);
				setPositionData(
					particlesCount, (gl::GLfloat) containerP[i].getPosition().x, (gl::GLfloat) containerP[i].getPosition().y,
					(gl::GLfloat) containerP[i].getPosition().z, (gl::GLfloat)containerP[i].getSize()
				);
				setColorData(
					particlesCount, (gl::GLubyte) containerP[i].getR(), (gl::GLubyte) containerP[i].getG(),
					(gl::GLubyte) containerP[i].getB(), (gl::GLubyte) containerP[i].getA()
				);
			} else {
				containerP[i].setCameraDistance(-1);
			}
			particlesCount = particlesCount + 1;
		}
	}
	sortParticles();
	//drawParticles(particlesCount);
}