#include "Particle.h"
#include <iostream>

/**	Call this function on each attribute_name of buffer
 **/
Particle::Particle() {
	life = -1;
}

/** Call this function on each attribute_name of buffer
 **/
Particle::~Particle() {
	
}

void Particle::decreaseLife(float decreasedValue) {
	life = life - decreasedValue;
}

glm::vec3 Particle::getPosition() {
	return (position);
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
	return (size);
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

void Particle::setLife(float inputLife) {
	life = inputLife;
}

void Particle::setPosition(glm::vec3 inputPosition) {
	position = inputPosition;
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
	size = inputSize;
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

void Particle::simulateGravity() {
	// Simulate simple physics : gravity only, no collisions
	/*speed += glm::vec3(0.0f,-9.81f, 0.0f) * (float)delta * 0.5f;
	position += speed * (float)delta;
	cameradistance = glm::length2(pos - CameraPosition );*/
	//ParticlesContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;
}