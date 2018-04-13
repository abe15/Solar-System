
#ifndef _PARTICLE
#define _PARTICLE
#include <cmath>
#include <math.h>
#include <cstdlib>
#include <time.h>

const int NUMBER_OF_PARTICLES = 3000;
const float MAX_ROTATION = 360;
const float MIN_ROTATION = 0;
const float MIN_TRANS = .005;
const float MAX_TRANS = .03;
const float MIN_DELTA_ROTATION = 0.5;
const float MAX_DELTA_ROTATION = 3.0;
const float MIN_DELTA_SURFACE = .005;
const float MAX_DELTA_SURFACE = .01;
const int MIN_LIFETIME = 10;
const int MAX_LIFETIME = 25;
const int DELTA_LIFETIME = 1;


struct Particle{
		//Used For Randomizing The Initial Position of the Particle
		float azimuthRoation, zenithRotation, surfaceTranslationFactor;

		//Used For Randomizing The Delta or Change In Position of Each Particle
		float deltaAz, deltaZe, deltaSurface;

		//Lifetime In "Refreshes"
		int lifetime;
};
		
class ParticleSystem{
	
	public: 
		//Gets the next particle in the array
		Particle getNextParticle();
		//Modify all particles by their deltas, destroy old ones and create new ones
		//if the lifetime is 0
		void updateAll();
		int getNumberOfParticles();
		ParticleSystem();


	private:
		//Marker used by getNextParticle to keep track of position.
		int currentParticle;

		//Array of all particle structs
		Particle particles[NUMBER_OF_PARTICLES];

	  //This is your random number generator from the last program
		float generateRandomNumber(float lower, float upper);
		
		//Get a new Particle struct with new randomized values.
		Particle generateNewParticle();

};



#endif