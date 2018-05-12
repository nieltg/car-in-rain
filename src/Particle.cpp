#include "Particle.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h> 

/**	Call this function on each attribute_name of buffer
 **/
Particle::Particle() {
	life = -1;
	cameradistance = -1;
}

/** Call this function on each attribute_name of buffer
 **/
Particle::~Particle() {
	
}

void Particle::decreaseLife(float decreasedValue) {
	life = life - decreasedValue;
}

glm::vec3 Particle::getPosition() {
	return (positions);
}

glm::vec3 Particle::getSpeed() {
	return (speed);
}

unsigned char Particle::getR() {
	return (r);
}

unsigned char Particle::getG() {
	return (g);
}

unsigned char Particle::getB() {
	return (b);
}

unsigned char Particle::getA() {
	return (a);
}

float Particle::getSize() {
	return (sizes);
}

float Particle::getAngle() {
	return (angle);
}

float Particle::getWeight() {
	return (weight);
}

float Particle::getCameraDistance() {
	return (cameradistance);
}

bool Particle::isAlive() {
	return (life >= 0);
}

bool Particle::isDead() {
	return (life < 0);
}

bool Particle::operator<(Particle& that) {
	// Sort in reverse order : far particles drawn first.
	return this->cameradistance > that.cameradistance;
}

void Particle::revive(float lifeInput, glm::vec3 startPosition, glm::vec3 maindir, float spread) {
	life = lifeInput;
	positions = startPosition;

	float pi = 3.14;
	srand (time(NULL));
	int phi = rand() % (2 * (int) pi);
	srand (time(NULL));
	int costheta = rand() % 1 - 2;
	srand (time(NULL));
	int u = rand() % 1;

	float theta = acos( costheta );
	float radius = spread * cbrt( u );

	float x = radius * sin( theta) * cos( phi );
	float y = radius * sin( theta) * sin( phi );
	float z = radius * cos( theta );

	glm::vec3 randomdir = glm::vec3(x,y,z);
	speed = maindir + randomdir * spread;

	srand (time(NULL));
	r = (unsigned char) rand() % 256;
	srand (time(NULL));
	g = (unsigned char) rand() % 256;
	srand (time(NULL));
	b = (unsigned char) rand() % 256;
	srand (time(NULL));
	a = (unsigned char) (rand() % 256) / 3;

	srand (time(NULL));
	sizes = (rand()%1000)/2000.0f + 0.1f;
}

void Particle::setLife(float inputLife) {
	life = inputLife;
}

void Particle::setPosition(glm::vec3 inputPosition) {
	positions = inputPosition;
}

void Particle::setSpeed(glm::vec3 inputSpeed) {
	speed = inputSpeed;
}

void Particle::setR(unsigned char inputR) {
	r = inputR;
}

void Particle::setG(unsigned char inputG) {
	g = inputG;
}

void Particle::setB(unsigned char inputB) {
	b = inputB;
}

void Particle::setA(unsigned char inputA) {
	a = inputA;
}

void Particle::setSize(float inputSize) {
	sizes = inputSize;
}

void Particle::setAngle(float inputAngle) {
	angle = inputAngle;
}

void Particle::setWeight(float inputWeight) {
	weight = inputWeight;
}

void Particle::setCameraDistance(float inputDistance) {
	cameradistance = inputDistance;
}

void Particle::simulateGravity(double deltaTime, glm::vec3 cameraPosition) {
	// Simulate simple physics : gravity only, no collisions
	speed = speed + glm::vec3(0.0f,-9.81f, 0.0f) * (float)deltaTime * 0.5f;
	positions = positions + speed * (float)deltaTime;
	cameradistance = glm::length(positions - cameraPosition );
	//ParticlesContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;
}