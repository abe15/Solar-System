#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(){
	currentParticle = 0;
	for(int i = 0; i < NUMBER_OF_PARTICLES; i++){
		particles[i] = generateNewParticle();
	}
}

Particle ParticleSystem::generateNewParticle(){
	Particle newPart;
		newPart.azimuthRoation = generateRandomNumber(MIN_ROTATION, MAX_ROTATION);
		newPart.zenithRotation = generateRandomNumber(MIN_ROTATION, MAX_ROTATION);
		newPart.surfaceTranslationFactor = generateRandomNumber(MIN_TRANS, MAX_TRANS);
		newPart.deltaAz = generateRandomNumber(MIN_DELTA_ROTATION, MAX_DELTA_ROTATION);
		newPart.deltaZe = generateRandomNumber(MIN_DELTA_ROTATION, MAX_DELTA_ROTATION);
		newPart.deltaSurface = generateRandomNumber(MIN_DELTA_SURFACE, MAX_DELTA_SURFACE);
		newPart.lifetime = (int)generateRandomNumber(MIN_LIFETIME, MAX_LIFETIME);
		return newPart;
}

Particle ParticleSystem::getNextParticle(){
	currentParticle = (currentParticle == NUMBER_OF_PARTICLES) ? 0 : currentParticle;
	return particles[currentParticle++];
}

int ParticleSystem::getNumberOfParticles(){
	return NUMBER_OF_PARTICLES;
}

float ParticleSystem::generateRandomNumber(float lower, float upper){
	static bool firstTime = true;
	time_t randomNumberSeed;

	if (firstTime){
		time(&randomNumberSeed);
		srand(randomNumberSeed);
		firstTime = false;
	}
	return (lower + ((upper - lower) * (float(rand()) / RAND_MAX)));
}

void ParticleSystem::updateAll(){	
	for(int i = 0; i < NUMBER_OF_PARTICLES; i++){
		if(particles[i].lifetime == 0){
			particles[i] = generateNewParticle();
		}else{
			particles[i].azimuthRoation += particles[i].deltaAz;
			particles[i].zenithRotation += particles[i].deltaZe;
			particles[i].surfaceTranslationFactor += particles[i].deltaSurface;
			particles[i].lifetime -= DELTA_LIFETIME;
		}
	}
}
