#include "ParticleContainer.h"
#include <iostream>
#include <algorithm>

/**	
 **/
ParticleContainer::ParticleContainer(int maxCountSize, GLfloat coord3d_input[], GLuint program) {
	MAX_PARTICLES = maxCountSize;
	containerP = new Particle[MAX_PARTICLES];
	position_size_data = new GLfloat[MAX_PARTICLES * 4];
	color_data = new GLubyte[MAX_PARTICLES * 4];

	Buffer coord_input = Buffer("particles_coord3d");
	Buffer color_input = Buffer("particles_color");
	Buffer position_input = Buffer("particles_position");

	buffer_coord = coord_input;
	buffer_color = color_input;
	buffer_position = position_input;

	buffer_coord.setBufferData(coord3d_input);
	buffer_color.setBufferData(MAX_PARTICLES);
	buffer_position.setBufferData(MAX_PARTICLES);

	buffer_coord.linkProgram(program);
	buffer_color.linkProgram(program);
	buffer_position.linkProgram(program);
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

void ParticleContainer::drawParticles(int particlesCount) {
	buffer_color.render(color_data,particlesCount,MAX_PARTICLES);
	buffer_position.render(position_size_data, particlesCount, MAX_PARTICLES);
	buffer_coord.render();

	buffer_coord.draw(particlesCount);
	buffer_color.renderClean();
	buffer_coord.renderClean();
	buffer_position.renderClean();
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
			result =  i;
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
					particlesCount, (GLfloat) containerP[i].getPosition().x, (GLfloat) containerP[i].getPosition().y,
					(GLfloat) containerP[i].getPosition().z, (GLfloat)containerP[i].getSize()
				);
				setColorData(
					particlesCount, (GLubyte) containerP[i].getR(), (GLubyte) containerP[i].getG(),
					(GLubyte) containerP[i].getB(), (GLubyte) containerP[i].getA()
				);
			} else {
				containerP[i].setCameraDistance(-1);
			}
			particlesCount = particlesCount + 1;
		}
	}
	sortParticles();
	drawParticles(particlesCount);
}

void ParticleContainer::setPositionData(int particlesCount, GLfloat x, GLfloat y, GLfloat z, GLfloat sizes) {
	position_size_data[4*particlesCount+0] = x;
	position_size_data[4*particlesCount+1] = y;
	position_size_data[4*particlesCount+2] = z;
	position_size_data[4*particlesCount+3] = sizes;
}

void ParticleContainer::setColorData(int particlesCount, GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
	color_data[4*particlesCount+0] = r;
	color_data[4*particlesCount+1] = g;
	color_data[4*particlesCount+2] = b;
	color_data[4*particlesCount+3] = a;
}

void ParticleContainer::sortParticles() {
	std::sort(&containerP[0], &containerP[MAX_PARTICLES]);
}