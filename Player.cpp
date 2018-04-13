#include "Player.h"

Player::Player()
{
	fade = true;
	//ship.Load("bunny.obj");
}
Player::~Player(){}
float rot = 0.0f;
void Player::Draw(Data *Data,Camera *Camera,Shader2 *Shader,bool glowVal)
{
	glPushMatrix();
	glTranslatef(GetX(),GetY(),GetZ());

	glRotatef(rot, 0, 1, 0);
	if(Camera->GetState() != STATE_FPS)
	{
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_PLAYER));
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_PLAYER_NMAP));
		glDisable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);

		glEnable(GL_BLEND);
		GLUquadricObj *q = gluNewQuadric();
		gluQuadricTexture(q,true);	
		Shader->SetUniform("colorMap", 0);
		Shader->SetUniform("normalMap", 1);
		Shader->SetUniform("invRadius", 0.0f);
		Shader->SetUniform("alpha", 1.0f);
		Shader->SetUniform("glowness", 0);
		Shader->SetUniform("posy", 0);
		if (glowVal) {
			Shader->Activate(PROGRAM_COMPLEX_NORMALMAP_LAVAGLOW);
				}
		else
		Shader->Activate(PROGRAM_ASTEROID);

		gluSphere(q,RADIUS,16,16);
		
		Shader->Deactivate();

		gluDeleteQuadric(q);
		glDisable(GL_BLEND);
	}

	glPopMatrix();
	rot++;
	if (rot == 361)
	{
		rot = 0;
	}
}

void Player::SetFade(bool b)
{
	fade = b;
}