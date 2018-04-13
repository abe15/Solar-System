#include "Camera.h"

Camera::Camera()
{
	yaw = 0.0f;
	last_yaw = 0.0f;
	pitch = -PI/2;
	distance = 0.4f;
	lambda = 1.0f;
	state = STATE_TPS;
}
Camera::~Camera(){}

void Camera::Refresh()
{
	vx = cos(yaw) * cos(pitch);
	vy = sin(pitch);
	vz = sin(yaw) * cos(pitch);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(x, y, z, x ,y,z+10,    0,1,0);

}

float Camera::GetLavaLambda(float Py,float Qy,float height)
{
	float Vy = Qy - Py;
	float D = -height;
	if(Vy == 0.0f) return 1.0f;
	float lambda = -(Py + D) / Vy;
	if(lambda < 0.0f || lambda > 1.0f) return 1.0f;
	return lambda;
}

void Camera::Update(float player_x,float player_y,float player_z)
{
	vx = cos(yaw) * cos(pitch);
	vy = sin(pitch);
	vz = sin(yaw) * cos(pitch);

	
	//if(GetState() == STATE_FPS) SetPos(player_x, player_y , player_z-10);
	if (GetState() == STATE_FPS)
		SetPos(x, y, player_z - 10);
	else
	{
		
		SetPos(x,y, player_z - 10);
	}
	SetPos(player_x, player_y, player_z - 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//gluLookAt(x, y, z, x + vx, y + vy, z + vz,    0,1,0);
	gluLookAt(x, y, z, player_x,player_y,player_z, 0, 1, 0);
 //   gluLookAt(x, y, z, x, 0, z+10, 0, 1, 0);
	//gluLookAt(x, y, z, 0, 0, player_z, 0, 1, 0);
	//glutSwapBuffers();
}

void Camera::SetState(int s)
{
	state = s;
}
int  Camera::GetState()
{
	return state;
}

void Camera::SetPos(float posx, float posy, float posz)
{
	x = posx;
	y = posy;
	z = posz;

	Refresh();
}

float Camera::GetDistance()
{
	return distance;
}

void Camera::GetDirectionVector(float &x, float &y, float &z)
{
    x = vx;
    y = vy;
    z = vz;
}

void Camera::RotateYaw(float angle)
{
	yaw += angle;

	Refresh();
}
void Camera::SetYaw(float angle)
{
	yaw = angle;
}
float Camera::GetYaw()
{
	return yaw;
}

void Camera::SetLastYaw(float angle)
{
	last_yaw = angle;
}
float Camera::GetLastYaw()
{
	return last_yaw;
}

void Camera::RotatePitch(float angle)
{
    const float limit = 89.0 * PI / 180.0;

	pitch += angle;

    if(pitch < -limit)
        pitch = -limit;

    if(pitch > limit)
        pitch = limit;

	Refresh();
}
void Camera::SetPitch(float angle)
{
	pitch = angle;
}
float Camera::GetPitch()
{
	return pitch;
}

float Camera::GetX()
{
	return x;
}
float Camera::GetY()
{
	return y;
}
float Camera::GetZ()
{
	return z;
}