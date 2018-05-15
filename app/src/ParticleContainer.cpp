#include "ParticleContainer.h"
#include <iostream>
#include <algorithm>

ParticleContainer::ParticleContainer() {
	MAX_PARTICLES = 1000;
	containerP = new Particle[MAX_PARTICLES];
	position_size_data = new gl::GLfloat[MAX_PARTICLES * 4];
	color_data = new gl::GLubyte[MAX_PARTICLES * 4];
}

/**	
 **/
ParticleContainer::ParticleContainer(int maxCountSize) {
	MAX_PARTICLES = maxCountSize;
	containerP = new Particle[MAX_PARTICLES];
	position_size_data = new gl::GLfloat[MAX_PARTICLES * 4];
	color_data = new gl::GLubyte[MAX_PARTICLES * 4];
}

/** 
 **/
ParticleContainer::~ParticleContainer() {
	delete[] containerP;
	delete[] position_size_data;
	delete[] color_data;

	containerP = NULL;
	position_size_data = NULL;
	color_data = NULL;
}

void ParticleContainer::createProgram() {
	// Shaders.
	g_vertexShaderSource = globjects::Shader::sourceFromFile("mesh.v.glsl");
	g_vertexShaderTemplate = globjects::Shader::applyGlobalReplacements(
		g_vertexShaderSource.get());
	g_vertexShader = globjects::Shader::create(
		gl::GL_VERTEX_SHADER, g_vertexShaderTemplate.get());

	if (!g_vertexShader->compile()) {
		throw std::runtime_error("Unable to compile vertex shader");
	}

	g_fragmentShaderSource = globjects::Shader::sourceFromFile("mesh.f.glsl");
	g_fragmentShaderTemplate = globjects::Shader::applyGlobalReplacements(
		g_fragmentShaderSource.get());
	g_fragmentShader = globjects::Shader::create(
		gl::GL_FRAGMENT_SHADER, g_fragmentShaderTemplate.get());

	if (!g_fragmentShader->compile()) {
		throw std::runtime_error("Unable to compile fragment shader");
	}

	program = globjects::Program::create();
	program->attach(g_vertexShader.get(), g_fragmentShader.get());

	program->link();

	attr_coord = program->getAttributeLocation("coord3d");
	attr_texcoord = program->getAttributeLocation("texcoord");
	attr_pos = program->getAttributeLocation("position");
	attr_color = program->getAttributeLocation("color");
	uniform_mvp = program->getUniformLocation("mvp");
	uniform_tex = program->getAttributeLocation("mytexture");

	program->setUniform(uniform_tex, 0);
}

void ParticleContainer::linkBuffer(std::vector<glm::vec3> vertices, std::vector<glm::vec2> texcoord, std::vector<gl::GLuint> indices,size_t indices_size) {
	indices_len = indices_size;
	
	// Buffer.
	m_vao = globjects::VertexArray::create();

	m_vertices = globjects::Buffer::create();
	m_vertices->setData(vertices, gl::GL_STATIC_DRAW);

	{
		auto vao_bind = m_vao->binding(0);
		vao_bind->setAttribute(attr_coord);
		vao_bind->setBuffer(m_vertices.get(), 0, sizeof(glm::vec3));
		vao_bind->setFormat(vertices.size(), gl::GL_FLOAT, gl::GL_FALSE, 0);
		m_vao->enable(0);
	}

	m_texcoord = globjects::Buffer::create();
	m_texcoord->setData(texcoord, gl::GL_STATIC_DRAW);

	{
		auto vao_bind = m_vao->binding(1);
		vao_bind->setAttribute(attr_texcoord);
		vao_bind->setBuffer(m_texcoord.get(), 0, sizeof(glm::vec2));
		vao_bind->setFormat(texcoord.size(), gl::GL_FLOAT, gl::GL_FALSE, 0);
		m_vao->enable(1);
	}

	m_indices = globjects::Buffer::create();
	m_indices->setData(indices, gl::GL_STATIC_DRAW);

	//BUFFER POSITION//
	GLfloat* g_particule_position_size_data = new GLfloat[MaxParticles * 4];
	GLubyte* g_particule_color_data         = new GLubyte[MaxParticles * 4];	
	//BUFFER POSITION//

	buffer_position = globjects::Buffer::create();
	buffer_position->setData();

	m_vao->bindElementBuffer(m_indices.get());
	
	/*Buffer coord_input = Buffer("particles_coord3d");
	//==glGenBuffers(1, &vbo_data);
	Buffer color_input = Buffer("particles_color");
	//==glGenBuffers(1, &vbo_data);
	Buffer position_input = Buffer("particles_position");
	//==glGenBuffers(1, &vbo_data);

	buffer_coord = coord_input;
	buffer_color = color_input;
	buffer_position = position_input;

	buffer_coord.setBufferData(coord3d_input);*/
	/*==
		glBindBuffer(GL_ARRAY_BUFFER, vbo_data);
		glBufferData(GL_ARRAY_BUFFER, sizeof(object_data), object_data, GL_STATIC_DRAW);
	*/
	//buffer_color.setBufferData(MAX_PARTICLES);
	/*==
		glBindBuffer(GL_ARRAY_BUFFER, vbo_data);
		glBufferData(GL_ARRAY_BUFFER, max_count * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
	*/
	//buffer_position.setBufferData(MAX_PARTICLES);
	/*==
		glBindBuffer(GL_ARRAY_BUFFER, vbo_data);
		glBufferData(GL_ARRAY_BUFFER, max_count * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
	*/

	//buffer_coord.linkProgram(program);
	//==attribute_coord = glGetAttribLocation(program, attribute_name);
	//buffer_color.linkProgram(program);
	//==attribute_coord = glGetAttribLocation(program, attribute_name);
	//buffer_position.linkProgram(program);
	//==attribute_coord = glGetAttribLocation(program, attribute_name);
}

void ParticleContainer::drawParticles(int particlesCount, glm::mat4 mvp) {
	gl::glActiveTexture(gl::GL_TEXTURE0);
	m_texture->bind();

	program->use();
	program->setUniform(uniform_mvp, mvp);
	m_vao->drawElements(gl::GL_TRIANGLES, indices_len, gl::GL_UNSIGNED_INT);
	program->release();

	m_texture->unbind();
	//buffer_color.render(color_data,particlesCount,MAX_PARTICLES);
	/*==
		glBindBuffer(GL_ARRAY_BUFFER, vbo_data);
		glBufferData(GL_ARRAY_BUFFER, max_count * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
		glBufferSubData(GL_ARRAY_BUFFER, 0, rendered_count * sizeof(GLubyte) * 4, object_data);

		glEnableVertexAttribArray(attribute_coord);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_data);
		glVertexAttribPointer(
			attribute_coord, // attribute. No particular reason for 1, but must match the layout in the shader.
			4, // size : r + g + b + a => 4
			GL_UNSIGNED_BYTE, // type
			GL_TRUE, // normalized? *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
			0, // stride
			(void*)0 // array buffer offset
		);
		glVertexAttribDivisor(attribute_coord, 1);
	*/
	//buffer_position.render(position_size_data, particlesCount, MAX_PARTICLES);
	/*==
		glBindBuffer(GL_ARRAY_BUFFER, vbo_data);
		glBufferData(GL_ARRAY_BUFFER, max_count * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
		glBufferSubData(GL_ARRAY_BUFFER, 0, rendered_count * sizeof(GLfloat) * 4, object_data);

		glEnableVertexAttribArray(attribute_coord);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_data);
		glVertexAttribPointer(
			attribute_coord, // attribute. No particular reason for 1, but must match the layout in the shader.
			4, // size : x + y + z + size => 4
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			0, // stride
			(void*)0 // array buffer offset
		);
		glVertexAttribDivisor(attribute_coord, 1);
	*/
	//buffer_coord.render();
	/*==
		glEnableVertexAttribArray(attribute_coord);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_data);
		glVertexAttribPointer(
			attribute_coord, // attribute. No particular reason for 0, but must match the layout in the shader.
			3, // size
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			0, // stride
			(void*)0 // array buffer offset
		);
		glVertexAttribDivisor(attribute_coord, 0);
	*/

	//buffer_coord.draw(particlesCount);
	//==glDrawArraysInstanced(gl::GL_TRIANGLE_STRIP, 0, 4, rendered_count);
	//buffer_color.renderClean();
	//==glDisableVertexAttribArray(attribute_coord);
	//buffer_coord.renderClean();
	//==glDisableVertexAttribArray(attribute_coord);
	//buffer_position.renderClean();
	//==glDisableVertexAttribArray(attribute_coord);
}

int ParticleContainer::findUnusedParticle() {
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

int ParticleContainer::getMaxParticles() {
	return (MAX_PARTICLES);
}

/**	double currentTime = glfwGetTime();
 *	double delta = currentTime - lastTime;
 *	lastTime = currentTime; 
 **/
void ParticleContainer::simulateParticles(double deltaTime, glm::vec3 cameraPosition) {
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

void ParticleContainer::setPositionData(int particlesCount, gl::GLfloat x, gl::GLfloat y, gl::GLfloat z, gl::GLfloat sizes) {
	position_size_data[4*particlesCount+0] = x;
	position_size_data[4*particlesCount+1] = y;
	position_size_data[4*particlesCount+2] = z;
	position_size_data[4*particlesCount+3] = sizes;
}

void ParticleContainer::setColorData(int particlesCount, gl::GLubyte r, gl::GLubyte g, gl::GLubyte b, gl::GLubyte a) {
	color_data[4*particlesCount+0] = r;
	color_data[4*particlesCount+1] = g;
	color_data[4*particlesCount+2] = b;
	color_data[4*particlesCount+3] = a;
}

void ParticleContainer::sortParticles() {
	std::sort(&containerP[0], &containerP[MAX_PARTICLES]);
}

void ParticleContainer::setTexture() {
	auto res_texture = IMG_Load("mesh.png");

	m_texture = globjects::Texture::create(gl::GL_TEXTURE_2D);
	m_texture->setParameter(gl::GL_TEXTURE_MIN_FILTER, gl::GL_LINEAR);
	m_texture->setParameter(gl::GL_TEXTURE_MAG_FILTER, gl::GL_LINEAR);
	m_texture->setParameter(gl::GL_TEXTURE_WRAP_S, gl::GL_CLAMP_TO_EDGE);
	m_texture->setParameter(gl::GL_TEXTURE_WRAP_T, gl::GL_CLAMP_TO_EDGE);

	m_texture->image2D(
		0,
		gl::GL_RGBA,
		glm::ivec2(res_texture->w, res_texture->h),
		0,
		gl::GL_RGBA,
		gl::GL_UNSIGNED_BYTE,
		res_texture->pixels);

	SDL_FreeSurface(res_texture);
}
/*
void ParticleContainer::loadObj() {
	// OBJ loader.
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texcoord;
	std::vector<gl::GLuint> indices;

	{
		objl::Loader loader;

		if (!loader.LoadFile("mesh.obj")) {
			throw std::runtime_error("Unable to load mesh.obj");
		}

		for (const auto& v : loader.LoadedVertices) {
			const auto& pos = v.Position;
			vertices.push_back(glm::vec3(pos.X, pos.Y, pos.Z));
			const auto& tex = v.TextureCoordinate;
			texcoord.push_back(glm::vec2(tex.X, tex.Y));
		}

		indices = loader.LoadedIndices;
	}

	indices_len = indices.size();

	linkBuffer(vertices,texcoord,indices);
}*/

ParticleContainer& ParticleContainer::operator=(const ParticleContainer& other) {
	MAX_PARTICLES = other.MAX_PARTICLES;
	LastUsedParticle = other.LastUsedParticle;
	for (int i=0;i< other.MAX_PARTICLES; i++) {
		containerP[i] = other.containerP[i];
	}
	for (int i=0;i< other.MAX_PARTICLES * 4;i++) {
		position_size_data[i] = other.position_size_data[i];
		color_data[i] = other.color_data[i];
	}
	
	/*buffer_coord = buffer_coord;
	buffer_position = buffer_position;
	buffer_color = buffer_color;*/
}