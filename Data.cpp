#include "Data.h"

Data::Data(void) {}
Data::~Data(void){}

int Data::GetID(int img)
{
	return textures[img].GetID();
}

void Data::GetSize(int img, int *w, int *h)
{
	textures[img].GetSize(w,h);
}

bool Data::LoadImage(int img, char *filename, int type)
{
	int res;

	res = textures[img].Load(filename,type);
	if(!res) return false;

	return true;
}
bool Data::Load()
{
	int res;
	res = LoadImage(IMG_GRASS,"Textures/grass.png",GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_ROCK,"Textures/rock.png",GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_LAVA,"Textures/lava.png",GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_SKYBOX,"Textures/skybox.png",GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_PLAYER,"Textures/player.png",GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_PLAYER_NMAP,"Textures/playerNmap.png",GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_CIRCLE_ON,"Textures/circle_on.png",GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_CIRCLE_OFF,"Textures/circle_off.png",GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_VORTEX,"Textures/vortex.png",GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_KEY,"Textures/key.png",GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_KEY_NMAP,"Textures/keyNmap.png",GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_PORTAL,"Textures/portal.png",GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_PORTAL_NMAP,"Textures/portalNmap.png",GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_COLUMN,"Textures/column.png",GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_COLUMN_NMAP,"Textures/columnNmap.png",GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_ASTEROID_1, "Textures/asteroid1.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_ASTEROID_2, "Textures/asteroid2.png", GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_SUN_1, "Textures/lava.png", GL_RGBA);
	if (!res) return false;
	//res = LoadImage(IMG_WATER_1, "Textures/reflection.png", GL_RGBA);
	//if (!res) return false;

	return true;
}