
#ifndef _CGAMEH_
#define _CGAMEH_
#include <vector>
#include <iostream>
#include "Player.h"
#include "Asteroid.h"
#include "PlayerInterface.h"
#include "Skybox.h"
#include "noiseutils.h"

#include "Data.h"
#include "TerrainGenerator.h"
#include "SolarSystem.h"
#include "shader.h"
#include "Sound.h"
//#include "ParticleSystem.h"
#define SCREEN_WIDTH	1280
#define SCREEN_HEIGHT	720

#define FRAMERATE 60
#define GRAVITY 0.015f

#define VERTEX_SHADER_PATH "terrain.vert"
#define FRAGMENT_SHADER_PATH "terrain.frag"
enum{
	STATE_LIVELOSS,
	STATE_RUN,
	STATE_ENDGAME
};
Skybox sky;
#define TOTAL_LEVELS	  1

//controls
#define P_UP		'w'
#define P_DOWN		's'
#define P_LEFT		'a'
#define P_RIGHT		'd'
#define P_JUMP		' '
#define P_PLUS		'+'
#define P_MINUS		'-'
#define NUM_ASTEROIDS 100
class GameEngine
{
public:
	GameEngine(void);
	virtual ~GameEngine(void);

	bool Init(int lvl);
	bool Loop();
	void Finalize();
	GLint shader_Program_2;
	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadSpecialKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	void ReadMouseMotion(int x, int y);
	//Process
	bool Process();
	//Output
	void Reshape(int w, int h);
	void Render();
	static float	z(const float x, const float y, const float t)
	{
		const float x2 = x - 3;
		const float y2 = y + 1;
		const float xx = x2 * x2;
		const float yy = y2 * y2;
		return ((2 * sinf(20 * sqrtf(xx + yy) - 4 * t) +
			noise::ValueNoise3D(10 * x, 10 * y, t, 0)) / 200);
		//Noise(10 * x, 10 * y, t, 0)) / 200);

	}
	void DrawWater();
	void DrawSun();
	Data Data;
private:
	unsigned char keys[256];
	bool mouse_left_down,mouse_right_down;
	int level,state,respawn_id,pickedkey_id;
	bool noclip;
	bool portal_activated;
	float time,ang, noclipSpeedF;	
	//cScene Scene;
	
	Player Player;
	Camera Camera;
	std::vector<Asteroid> asteroidList;	
	Shader2 ccShader;
	Sound music;
	

	void Physics(PlayerInterface &object);
};

#endif