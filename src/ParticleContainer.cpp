#include "ParticleContainer.h"
#include <iostream>
#include <algorithm>

/**	
 **/
ParticleContainer::ParticleContainer() {
	MAX_PARTICLES = 1000;
	containerP = new Particle[MAX_PARTICLES];
}

ParticleContainer::ParticleContainer(int maxCountSize) {
	MAX_PARTICLES = maxCountSize;
	containerP = new Particle[MAX_PARTICLES];
}

/** 
 **/
ParticleContainer::~ParticleContainer() {
	delete[] containerP;
	containerP = NULL;
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

void ParticleContainer::simulateParticles() {
	/*int newparticles = (int)(deltaTime*10000.0);
	if (newparticles > (int)(0.016f*10000.0)) {
		newparticles = (int)(0.016f*10000.0);
	}

	int ParticlesCount = 0;
	for(int i=0; i<MaxParticles; i++){

		Particle& p = ParticlesContainer[i]; // shortcut

		if(p.life > 0.0f){

			// Decrease life
			p.life -= delta;
			if (p.life > 0.0f){

				

				// Fill the GPU buffer
				g_particule_position_size_data[4*ParticlesCount+0] = p.pos.x;
				g_particule_position_size_data[4*ParticlesCount+1] = p.pos.y;
				g_particule_position_size_data[4*ParticlesCount+2] = p.pos.z;

				g_particule_position_size_data[4*ParticlesCount+3] = p.size;

				g_particule_color_data[4*ParticlesCount+0] = p.r;
				g_particule_color_data[4*ParticlesCount+1] = p.g;
				g_particule_color_data[4*ParticlesCount+2] = p.b;
				g_particule_color_data[4*ParticlesCount+3] = p.a;

			}else{
				// Particles that just died will be put at the end of the buffer in SortParticles();
				p.cameradistance = -1.0f;
			}

			ParticlesCount++;

		}
	}
	sortParticles();*/
}

void ParticleContainer::sortParticles() {
	std::sort(&containerP[0], &containerP[MAX_PARTICLES]);
}