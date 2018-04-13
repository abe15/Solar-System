#include "PlayerInterface.h"

PlayerInterface::PlayerInterface(void)
{
	SetVel(0.0,0.0,0.0);
	yaw = 0.0f; pitch = 0.0f;
}
PlayerInterface::~PlayerInterface(void){}

void PlayerInterface::SetPos(float posx, float posy, float posz)
{
	x = posx;
	y = posy;
	z = posz;
}
void PlayerInterface::SetX(float posx)
{
	x = posx;
}
void PlayerInterface::SetY(float posy)
{
	y = posy;
}
void PlayerInterface::SetZ(float posz)
{
	z = posz;
}
float PlayerInterface::GetX()
{
    return x;
}
float PlayerInterface::GetY()
{
    return y;
}
float PlayerInterface::GetZ()
{
    return z;
}

void PlayerInterface::SetVel(float velx, float vely, float velz)
{
	vx = velx;
	vy = vely;
	vz = velz;
}
void PlayerInterface::SetVX(float velx)
{
	vx = velx;
}
void PlayerInterface::SetVY(float vely)
{
	vy = vely;
}
void PlayerInterface::SetVZ(float velz)
{
	vz = velz;
}
float PlayerInterface::GetVX()
{
    return vx;
}
float PlayerInterface::GetVY()
{
    return vy;
}
float PlayerInterface::GetVZ()
{
    return vz;
}

void PlayerInterface::SetYaw(float ang)
{
	yaw = ang;
}
void PlayerInterface::SetPitch(float ang)
{
	pitch = ang;
}
float PlayerInterface::GetYaw()
{
	return yaw;
}
float PlayerInterface::GetPitch()
{
	return pitch;
}

void PlayerInterface::SetState(int s)
{
	state = s;
}
int PlayerInterface::GetState()
{
	return state;
}

void PlayerInterface::SetMaxHealth(int max_h)
{
	max_health = max_h;
}
int PlayerInterface::GetMaxHealth()
{
	return max_health;
}
void PlayerInterface::SetHealth(int h)
{
	health = h;
}
int PlayerInterface::GetHealth()
{
	return health;
}