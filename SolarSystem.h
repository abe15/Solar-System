#ifndef SOLAR_H
#define SOLAR_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <math.h>
#include "SolarSystemGlobals.h"
#include "ParticleSystem.h"
#include "Shader2.h"
#include "RGBpixmap.h" 

class SolarSystem {
public:
	void MakeAllImages();
	void MakeImage(const char bitmapFilename[], GLuint &textureName, bool hasAlpha);

	void drawEarthAndMoon();

	void drawSun(Shader2* Shader,bool gloVal);
	void drawSaturnRing();
	void drawAllPlanets();
	void drawGenericPlanet(GLfloat inclination, GLfloat orbitDuration,
		GLfloat orbitRadius, GLfloat rotationDuration, GLuint texturename, GLfloat radius);
	void drawParticle(Particle currParticle);
	void drawAllParticles();
	GLuint ParticleTextureName = -1;
	GLuint EarthTextureName = 3;
	GLuint MoonTextureName = 4;


	GLuint SunTextureName = 0;
	GLuint MercuryTextureName = 1;

	GLuint VenusTextureName = 2;
	GLuint MarsTextureName = 5;
	GLuint JupiterTextureName = 6;
	GLuint SaturnTextureName = 7;
	GLuint UranusTextureName = 8;
	GLuint NeptuneTextureName = 9;
	GLuint PlutoTextureName = 10;
	GLuint RingTextureName = 11;

	GLfloat CurrentEarthRotation = 0.00;
	GLfloat EarthDaysTranspired = 0.00;
	GLfloat EarthDayIncrement = 0.01 * 10;
	GLint currWindowSize[2] = { 1920, 1080 };
	GLint currViewportSize[2] = { 1920, 1080 };
	ParticleSystem particles;
	bool particleFlag = true;
	bool blendFlag = true;
};

#endif // !SOLAR_H

