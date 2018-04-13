#include <stdlib.h>
#include <time.h>
#include "Data.h"
#include "Camera.h"
//#include "Shader2.h"
#include <cmath>
#ifndef _ASTERIOD
#define _ASTEROID
//#define RADIUS   0.5f
class Asteroid
	{
		static int list;
		//static rand r = new rand();
		float x, y, z;
		float incX;
		float incY;
		float asteroidSpeed;
		float radius;
		float rot;
		int texture;
		bool crashed;

	public:
		bool Crashed();
		
		float GetX();
		float GetY();
		float GetZ();
		void SetX(float);
		void SetY(float);
		void SetZ(float);
	

		Asteroid();
		

		void Reset();
		

		void Create();
		
		void Draw(Data *Data );//, Shader2 *Shader);
		
};

#endif