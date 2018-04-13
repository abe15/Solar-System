#pragma once

#include "Texture.h"

//Image array size
#define NUM_TEX		 18

//Image identifiers
enum {
	IMG_GRASS,
	IMG_ROCK,
	IMG_LAVA,
	IMG_SKYBOX,
	IMG_PLAYER,
	IMG_PLAYER_NMAP,
	IMG_CIRCLE_ON,
	IMG_CIRCLE_OFF,
	IMG_VORTEX,
	IMG_KEY,
	IMG_KEY_NMAP,
	IMG_PORTAL,
	IMG_PORTAL_NMAP,
	IMG_COLUMN,
	IMG_COLUMN_NMAP,
	IMG_ASTEROID_1,
	IMG_ASTEROID_2,
	IMG_SUN_1,
	//IMG_WATER_2
};

class Data
{
public:
	Data(void);
	~Data(void);

	int  GetID(int img);
	void GetSize(int img, int *w, int *h);
	bool Load();

private:
	Texture textures[NUM_TEX];
	bool LoadImage(int img,char *filename,int type = GL_RGBA);
};
