#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glbinding/gl/gl.h>
//#include <GL/glew.h>

class Particle {
	private :
		glm::vec3 positions;
		glm::vec3 speed;
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
		float sizes;
		float angle;
		float weight;
		float life; // Remaining life of the particle. if < 0 : dead and unused.
		float cameradistance;
		
	public :
		Particle();
		~Particle();
		void decreaseLife(float decreasedValue);
		int getMaxParticles();
		glm::vec3 getPosition();
		glm::vec3 getSpeed();
		unsigned char getR();
		unsigned char getG();
		unsigned char getB();
		unsigned char getA();
		float getSize();
		float getAngle();
		float getWeight();
		float getCameraDistance();
		bool isAlive();
		bool isDead();
		bool operator<(Particle& that);
		void revive(float lifeInput, glm::vec3 startPosition, glm::vec3 maindir, float spread);
		void setLife(float inputLife);
		void setPosition(glm::vec3 inputPosition);
		void setSpeed(glm::vec3 inputSpeed);
		void setR(unsigned char inputR);
		void setG(unsigned char inputG);
		void setB(unsigned char inputB);
		void setA(unsigned char inputA);
		void setSize(float inputSize);
		void setAngle(float inputAngle);
		void setWeight(float inputWeight);
		void setCameraDistance(float inputDistance);
		void simulateGravity(double deltaTime, glm::vec3 cameraPosition);
		Particle& operator=(const Particle& other);
};