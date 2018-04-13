#pragma once

#include "PlayerInterface.h"
#include "Camera.h"
#include "Data.h"
#include "Shader2.h"

#define PLAYER_SPEED  0.008f
#define PLAYER_JUMP_SPEED  0.4f
#define FRICTION   0.05f
#define ELASTICITY   0.5f 
#define MAX_MOVEMENT 0.4f
#define RADIUS   2.0f

class Player: public PlayerInterface
{
public:
	Player();
	~Player();
	//Model_OBJ ship;
	void Draw(Data *Data,Camera *Camera,Shader2 *Shader,bool glowVal);
	void SetFade(bool b);

private:
	bool fade;
	
};