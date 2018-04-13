#include "Asteroid.h"
#include <stdlib.h>

	


bool Asteroid::Crashed() {}

	float Asteroid::GetX() {
		return x;
	}
	float Asteroid::GetY() {
		return y;
	}
	float Asteroid::GetZ() {
		return z;
	}
	void Asteroid::SetX(float x1) {
		this->x = x1;
	}
	void Asteroid::SetY(float y1) {
		this->y = y1;
	}
	void Asteroid::SetZ(float z1) {
		this->z = z1;
	}


	Asteroid::Asteroid() {
		x = y = z = 0;
		srand(time(NULL));
		Reset();
		texture = (rand() % 2) +15;	
	}


	void Asteroid::Reset() {
		x = (rand()%11) * (float)pow(-1, rand());
		z = (35 + (rand()%35)) * -1;
		y = (rand()%8) * (float)pow(-1,rand());
		//x = (rand()) * (float)pow(-1, rand());
		//y = (rand()) * (float)pow(-1, rand());
		//z = (35 + (rand())) * -1;
		x = int(x) % 100;
		y = int(y) % 100;
		z = int(z) % 100;
		radius = (float)(1/rand() * 2);
		//radius = 50.0f;
		//radius = int(radius) % 100;
		if (x > 0)
			incX = (float)(((double)rand() / (RAND_MAX))) * -1;
		else
			incX = (float)(1/rand());

		if (y > 0)
			incY = (float)(((double)rand() / (RAND_MAX))) * -1;
		else
			incY = (float)(((double)rand() / (RAND_MAX)));

		incX *= 0.03f;
		incY *= 0.03f;
		asteroidSpeed = (float)(((double)rand() / (RAND_MAX)) * 0.1);
	
	
	}


	void Asteroid::Create() {}

	void Asteroid::Draw(Data *Data)//, Shader2 *Shader) 
	{

		z += asteroidSpeed;
		y += incY;
		x += incX;
		rot += 1.0f;

		

		GLUquadricObj *q = gluNewQuadric();
		gluQuadricNormals(q, GLU_SMOOTH);
		gluQuadricTexture(q, true);
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();

		glRotatef(rot, 1, 1, 1);
		glTranslatef(GetX(), GetY(), GetZ());

		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, texture);
		glBindTexture(GL_TEXTURE_2D, Data->GetID(IMG_ASTEROID_1));
		//glDisable(GL_TEXTURE_2D);
		//glActiveTexture(GL_TEXTURE0);

	//	glEnable(GL_BLEND);
		
		/*
		Shader->Activate(PROGRAM_ASTEROID);
		Shader->SetUniform("tex_top", 0);
		Shader->SetUniform("tex_side", 1);
		Shader->SetUniform("height", Lava->GetHeight());
		Shader->SetUniform("hmax", Lava->GetHeightMax());*/
		gluSphere(q, radius, 16, 16);		
		//Shader->Deactivate();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		gluDeleteQuadric(q);
		//glDisable(GL_BLEND);
		
		
		//glFlush();

	}


