#include "GameEngine.h"

#include <jpeglib.h>
#include <jerror.h>
GameEngine::GameEngine(void) {}
GameEngine::~GameEngine(void){}
/*Terrain variables*/
float cube_size = 32.0f;
int wireframeMode = 0;
float seed_0 = 10;
float seed_1 = 22;
float seed_2 = 5;
float seed_3 = 5.1;
float player_z = 50.0f;
bool drawPlanets = false;
bool drawParticles = false;
bool drawTerrain = false;
bool drawWaterQ = false;
TerrainGenerator *tg;
#define SUN_RADIUS 50.0f
/*Water Variables*/
#define	RESOLUTION 1000
static GLuint	texture;
bool glowOn = false;
int seed_values = 0;
static int	left_click = GLUT_UP;
static int	right_click = GLUT_UP;
static int	wire_frame = 0;
static int	normals = 0;
static int	xold = 0;
static int	yold = 0;
static float	rotate_x = 30;
static float	rotate_y = 15;
static float	translate_z = 4;

static float	surface[6 * RESOLUTION * (RESOLUTION + 1)];
static float	normal[6 * RESOLUTION * (RESOLUTION + 1)];
SolarSystem sol = SolarSystem();


int		load_texture(const char * filename,
	unsigned char * dest,
	const int format,
	const unsigned int size)
{
	FILE *fd;
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	unsigned char * line;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	if (0 == (fd = fopen(filename, "rb")))
		return 1;

	jpeg_stdio_src(&cinfo, fd);
	jpeg_read_header(&cinfo, TRUE);
	if ((cinfo.image_width != size) || (cinfo.image_height != size))
		return 1;

	if (GL_RGB == format)
	{
		if (cinfo.out_color_space == JCS_GRAYSCALE)
			return 1;
	}
	else
		if (cinfo.out_color_space != JCS_GRAYSCALE)
			return 1;

	jpeg_start_decompress(&cinfo);

	while (cinfo.output_scanline < cinfo.output_height)
	{
		line = dest +
			(GL_RGB == format ? 3 * size : size) * cinfo.output_scanline;
		jpeg_read_scanlines(&cinfo, &line, 1);
	}
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	return 0;
}
/*
** water draw
*/
void GameEngine::DrawWater(void)
{
	
	const float t = glutGet(GLUT_ELAPSED_TIME) / 1000.;
	const float delta = 2. / RESOLUTION;
	const unsigned int length = 2 * (RESOLUTION + 1);
	const float xn = (RESOLUTION + 1) * delta + 1;
	unsigned int i;
	unsigned int j;
	float x;
	float y;
	unsigned int indice;
	unsigned int preindice;

	/* Yes, I know, this is quite ugly... */
	float v1x;
	float v1y;
	float v1z;

	float v2x;
	float v2y;
	float v2z;

	float v3x;
	float v3y;
	float v3z;

	float vax;
	float vay;
	float vaz;

	float vbx;
	float vby;
	float vbz;

	float nx;
	float ny;
	float nz;

	float l;


	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(0, 0, -translate_z);
	glRotatef(rotate_y, 1, 0, 0);
	glRotatef(rotate_x, 0, 1, 0);

	/* Vertices */
	for (j = 0; j < RESOLUTION; j++)
	{
		y = (j + 1) * delta - 1;
		for (i = 0; i <= RESOLUTION; i++)
		{
			indice = 6 * (i + j * (RESOLUTION + 1));

			x = i * delta - 1;
			surface[indice + 3] = x;
			surface[indice + 4] = z(x, y, t);
			surface[indice + 5] = y;
			if (j != 0)
			{
				/* Values were computed during the previous loop */
				preindice = 6 * (i + (j - 1) * (RESOLUTION + 1));
				surface[indice] = surface[preindice + 3];
				surface[indice + 1] = surface[preindice + 4];
				surface[indice + 2] = surface[preindice + 5];
			}
			else
			{
				surface[indice] = x;
				surface[indice + 1] = z(x, -1, t);
				surface[indice + 2] = -1;
			}
		}
	}

	/* Normals */
	for (j = 0; j < RESOLUTION; j++)
		for (i = 0; i <= RESOLUTION; i++)
		{
			indice = 6 * (i + j * (RESOLUTION + 1));

			v1x = surface[indice + 3];
			v1y = surface[indice + 4];
			v1z = surface[indice + 5];

			v2x = v1x;
			v2y = surface[indice + 1];
			v2z = surface[indice + 2];

			if (i < RESOLUTION)
			{
				v3x = surface[indice + 9];
				v3y = surface[indice + 10];
				v3z = v1z;
			}
			else
			{
				v3x = xn;
				v3y = z(xn, v1z, t);
				v3z = v1z;
			}

			vax = v2x - v1x;
			vay = v2y - v1y;
			vaz = v2z - v1z;

			vbx = v3x - v1x;
			vby = v3y - v1y;
			vbz = v3z - v1z;

			nx = (vby * vaz) - (vbz * vay);
			ny = (vbz * vax) - (vbx * vaz);
			nz = (vbx * vay) - (vby * vax);

			l = sqrtf(nx * nx + ny * ny + nz * nz);
			if (l != 0)
			{
				l = 1 / l;
				normal[indice + 3] = nx * l;
				normal[indice + 4] = ny * l;
				normal[indice + 5] = nz * l;
			}
			else
			{
				normal[indice + 3] = 0;
				normal[indice + 4] = 1;
				normal[indice + 5] = 0;
			}


			if (j != 0)
			{
				/* Values were computed during the previous loop */
				preindice = 6 * (i + (j - 1) * (RESOLUTION + 1));
				normal[indice] = normal[preindice + 3];
				normal[indice + 1] = normal[preindice + 4];
				normal[indice + 2] = normal[preindice + 5];
			}
			else
			{
				/* 	    v1x = v1x; */
				v1y = z(v1x, (j - 1) * delta - 1, t);
				v1z = (j - 1) * delta - 1;

				/* 	    v3x = v3x; */
				v3y = z(v3x, v2z, t);
				v3z = v2z;

				vax = v1x - v2x;
				vay = v1y - v2y;
				vaz = v1z - v2z;

				vbx = v3x - v2x;
				vby = v3y - v2y;
				vbz = v3z - v2z;

				nx = (vby * vaz) - (vbz * vay);
				ny = (vbz * vax) - (vbx * vaz);
				nz = (vbx * vay) - (vby * vax);

				l = sqrtf(nx * nx + ny * ny + nz * nz);
				if (l != 0)
				{
					l = 1 / l;
					normal[indice] = nx * l;
					normal[indice + 1] = ny * l;
					normal[indice + 2] = nz * l;
				}
				else
				{
					normal[indice] = 0;
					normal[indice + 1] = 1;
					normal[indice + 2] = 0;
				}
			}
		}
	/**/
	 //The ground 
		/*
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_TEXTURE_2D);
	glColor3f(1, -.2, 0.7);
	glTranslatef(0, -.02, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(-1, 0, -1);
	glVertex3f(-1, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, -1);
	glEnd();
	*/
	//glTranslatef(0, 0.2, 0);
	
	/* Render wireframe? */
	if (wire_frame != 0)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	/* The water */
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0, 0.2, 0);
	glColor3f(1, 1, 1);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normal);
	glVertexPointer(3, GL_FLOAT, 0, surface);
	for (i = 0; i < RESOLUTION; i++)
		glDrawArrays(GL_TRIANGLE_STRIP, i * length, length);

	glDisable(GL_TEXTURE_2D);
	/* Draw normals? */
	if (false)
	{
		
		glColor3f(1, 0, 0);
		glBegin(GL_LINES);
		for (j = 0; j < RESOLUTION; j++)
			for (i = 0; i <= RESOLUTION; i++)
			{
				indice = 6 * (i + j * (RESOLUTION + 1));
				glVertex3fv(&(surface[indice]));
				glVertex3f(surface[indice] + normal[indice] / 50,
					surface[indice + 1] + normal[indice + 1] / 50,
					surface[indice + 2] + normal[indice + 2] / 50);
			}

		glEnd();
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	/* End */
	//glFlush();
	//glutSwapBuffers();
	//glutPostRedisplay();

}


bool GameEngine::Init(int lvl)
{
	bool res = true;
	noclip = false;
	portal_activated = false;
	time = ang = 0.0f;
	noclipSpeedF = 1.0f; 
	level = lvl;
	state = STATE_RUN;
	respawn_id = 0;
	pickedkey_id = -1;
	sky.Load(CAMERA_ZFAR);
	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0,(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,CAMERA_ZNEAR,CAMERA_ZFAR);
	glMatrixMode(GL_MODELVIEW);
	music.Load();
	sol.MakeAllImages();
	const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
	const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//const GLfloat light_position[] = { 500.0f, 500.0f, 500.0f, 0.0f };
	const GLfloat light_position[] = {0.0f,SUN_RADIUS,0.0f, 0.0f };
	const GLfloat light_position_2[] = {SUN_RADIUS,0.0f,0.0f, 0.0f };
	const GLfloat light_position_3[] = { 0.0f,0.0f,SUN_RADIUS, 0.0f };

	const GLfloat light_position_4[] = { 0.0f,-SUN_RADIUS,0.0f, 0.0f };
	const GLfloat light_position_5[] = { -SUN_RADIUS,0.0f,0.0f, 0.0f };
	const GLfloat light_position_6[] = { 0.0f,0.0f,-SUN_RADIUS, 0.0f };

	const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
	const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
	const GLfloat mat_specular[]   = { 0.3f, 0.3f, 0.3f, 1.0f };
	const GLfloat mat_shininess[]  = { 100.0 };


	glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);	
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);

	glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular);

	glLightfv(GL_LIGHT4, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT4, GL_POSITION, light_position);

	glLightfv(GL_LIGHT5, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT5, GL_SPECULAR, light_specular);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	glLightfv(GL_LIGHT1, GL_POSITION, light_position_2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);

	glLightfv(GL_LIGHT2, GL_POSITION, light_position_3);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);

	glLightfv(GL_LIGHT3, GL_POSITION, light_position_4);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse);

	glLightfv(GL_LIGHT4, GL_POSITION, light_position_5);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, light_diffuse);

	glLightfv(GL_LIGHT5, GL_POSITION, light_position_6);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, light_diffuse);
	
	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	//glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glCullFace(GL_FRONT);
	
	//Texture initialization
	Data.Load();
	
	//level initialization(terrain, lava and skybox)
	//Scene.LoadLevel(level,CAMERA_ZFAR);
	GameEngine::shader_Program_2 = LoadShaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	tg = new TerrainGenerator(pow(2,8), cube_size,GameEngine::shader_Program_2);
	tg->start[0] = 100;// TERRAIN_SIZE / 2;
	tg->start[1] = -1000;//Terrain.GetHeight(TERRAIN_SIZE / 2, 0) + 200 * RADIUS;
	tg->start[2] = 100;
	tg->setCellSize(cube_size);
	tg->setSeed(seed_0, seed_1, seed_2, seed_3);
	tg->init();

	//Shader initialization
	
	ccShader.Load();
	Player.SetPos(0, 0, player_z);
	Camera.SetPos(0, 0, player_z - 10);
	for (int i = 0; i < NUM_ASTEROIDS; i++)
	{
		Asteroid *a = new Asteroid();
		asteroidList.push_back(*a);
	}
	unsigned char total_texture[4 * 256 * 256];
	unsigned char alpha_texture[256 * 256];
	unsigned char caustic_texture[3 * 256 * 256];
	unsigned int i;
	/* Texture loading  */
	glGenTextures(1, &texture);
	if (load_texture("Textures//alpha.jpg", alpha_texture, GL_ALPHA, 256) != 0 ||
		load_texture("Textures//reflection.jpg", caustic_texture, GL_RGB, 256) != 0)
		return 1;
	for (i = 0; i < 256 * 256; i++)
	{
		total_texture[4 * i] = caustic_texture[3 * i];
		total_texture[4 * i + 1] = caustic_texture[3 * i + 1];
		total_texture[4 * i + 2] = caustic_texture[3 * i + 2];
		total_texture[4 * i + 3] = alpha_texture[i];
	}
	glBindTexture(GL_TEXTURE_2D, texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, 256, 256, GL_RGBA,
		GL_UNSIGNED_BYTE, total_texture);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glEnable(GL_TEXTURE_GEN_S);
	//glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	
	
	//Player initialization
	//Player.SetPos(TERRAIN_SIZE/2,Terrain.GetHeight(TERRAIN_SIZE/2,TERRAIN_SIZE/2)+RADIUS,TERRAIN_SIZE/2);
	//Player.SetPos(TERRAIN_SIZE / 2, Terrain.GetHeight(TERRAIN_SIZE / 2, 0) + 200*RADIUS, player_z);
	//Camera.SetPos(TERRAIN_SIZE / 2, Terrain.GetHeight(TERRAIN_SIZE / 2, 0) + 200 * RADIUS, player_z-10);
	music.Play(SOUND_AMBIENT);

	return res;
}

bool GameEngine::Loop()
{
	bool res=true;
	int t1,t2;
	t1 = glutGet(GLUT_ELAPSED_TIME);

	if(state == STATE_RUN)
	{
		res = Process();
		if(res) Render();
	}
	else if(state == STATE_LIVELOSS)
	{
		Render();
		//Player.SetPos(respawn_points[respawn_id].GetX(),respawn_points[respawn_id].GetY()+RADIUS,respawn_points[respawn_id].GetZ());
		state = STATE_RUN;
	}
	else if(state == STATE_ENDGAME)
	{
		res=false;
	}

	do { t2 = glutGet(GLUT_ELAPSED_TIME);
	} while(t2-t1 < 1000/FRAMERATE);
	return res;
}

void GameEngine::Finalize()
{
}

//Input
void GameEngine::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	if(key >= 'A' && key <= 'Z') key += 32;
	keys[key] = press;

	if (key == '1'&& press)
	{
		wireframeMode = !wireframeMode;
	}
	if (key == '2' && press)
	{
		wire_frame = !wire_frame;
	}
	if (key == 't' && press)
	{
		seed_values++;
		if (seed_values == 9)
			seed_values = 0;
		switch (seed_values) {
		case 0:
			cube_size = 32.0F;
			seed_0 = 5;
			seed_1 = 10;
			seed_2 = 5;
			seed_3 = 10;
			break;
		case 1:
			cube_size = 48.0F;
			seed_0 = 0;
			seed_1 = 5;
			seed_2 = 0;
			seed_3 = 5;
			break;
		case 2:
			cube_size = 12.0F;
			seed_0 = 40;
			seed_1 = 50;
			seed_2 = 40;
			seed_3 = 50;

			break;
		case 3:
			cube_size = 1.0F;
			seed_0 = 14;
			seed_1 = 15;
			seed_2 = 200;
			seed_3 = 500;

			break;
		case 4:
			cube_size = 12.0F;
			seed_0 = 100;
			seed_1 = 100.5;
			seed_2 = 50;
			seed_3 = 1000;
			break;
		case 5:
			cube_size = 68.0F;
			seed_0 = 10;
			seed_1 = 20;
			seed_2 = 10;
			seed_3 = 20;
			break;
		case 6:
			cube_size = 128.0F;
			seed_0 = 0;
			seed_1 = 40;
			seed_2 = 0;
			seed_3 = 40;
			break;
		case 7:
			cube_size = 24.0F;
			seed_0 = 0;
			seed_1 = 1;
			seed_2 = 0;
			seed_3 = 1;
			break;
		case 8:
			cube_size = 24.0F;
			seed_0 = 0;
			seed_1 = 1;
			seed_2 = 0;
			seed_3 = 1;
			break;
		case 9:
			cube_size = 24.0F;
			seed_0 = 0;
			seed_1 = 10;
			seed_2 = 0;
			seed_3 = 10;
			break;
		
		}
	


		tg->setSeed(seed_0, seed_1, seed_2, seed_3);
		tg->setCellSize(cube_size);
		tg->init();

	}
	if (key == 'y' && press)
	{
		sol.EarthDayIncrement *= 2;
	}
	if (key == 'p' && press)
	{
		drawPlanets = !drawPlanets;
	}
	if (key == 'l' && press)
	{
		drawTerrain = !drawTerrain;
	}
	if (key == 'm' && press)
	{
		drawParticles = !drawParticles;
	}
	if (key == 'n' && press)
	{
		drawWaterQ = !drawWaterQ;
	}
	if (key == 'g' && press)
	{
		glowOn = !glowOn;
	}




}
void GameEngine::ReadSpecialKeyboard(unsigned char key, int x, int y, bool press)
{
	if(key == GLUT_KEY_F10 && press)
	{
		//if(!noclip) Sound.Play(SOUND_SCREWGRAVITY);
		noclip = !noclip;
		Player.SetVel(0.0f,0.0f,0.0f);
	}
}

void GameEngine::ReadMouse(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN) {
        if(button == GLUT_LEFT_BUTTON) {
            mouse_left_down = true;
        }
        else if(button == GLUT_RIGHT_BUTTON) {
            mouse_right_down = true;
        }
	
    }
    else if(state == GLUT_UP) {
        if(button == GLUT_LEFT_BUTTON) {
            mouse_left_down = false;
        }
        else if(button == GLUT_RIGHT_BUTTON) {
            mouse_right_down = false;
        }
    }
}

void GameEngine::ReadMouseMotion(int x, int y)
{
	// This variable is hack to stop glutWarpPointer from triggering an event callback to Mouse(...)
    // This avoids it being called recursively and hanging up the event loop
    static bool just_warped = false;

    if(just_warped) {
        just_warped = false;
        return;
    }
	
	
    int dx = x - SCREEN_WIDTH/2;
    int dy = y - SCREEN_HEIGHT/2;
	
    just_warped = true;
}

//Process
bool GameEngine::Process()
{
	bool res=true;
	
	//Process Input
	if(keys[27])	res=false;

	float vx,vy,vz;
	Camera.GetDirectionVector(vx,vy,vz);
	float factor = sqrt( 1.0f/(vx*vx + vz*vz) ) +10;
	float factor2 = factor;


		if(keys[P_UP])
		{
			Player.SetY(Player.GetY() + 15);
			
		}
		else if(keys[P_DOWN])
		{
			
			Player.SetY(Player.GetY() - 15);
			
			
		}
		if(keys[P_RIGHT])
		{
			Player.SetX(Player.GetX() - 15);
			
		}
		else if(keys[P_LEFT])
		{
			Player.SetX(Player.GetX() + 15);
			
		}
		if (keys['q'])
		{
			Player.SetZ(Player.GetZ() -15);
			
		}
		else if (keys['e'])
		{
			Player.SetZ(Player.GetZ()+15);
			
		}
		


	return res;
}

void GameEngine::Physics(PlayerInterface &object)
{	
}
void GameEngine::DrawSun()
{
	GLUquadricObj* quadro = gluNewQuadric();
	gluQuadricNormals(quadro, GLU_SMOOTH);
	gluQuadricTexture(quadro, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glTranslatef(2000, 2000, 2000);
	glBindTexture(GL_TEXTURE_2D, Data.GetID(IMG_SUN_1));
	gluSphere(quadro, SUN_RADIUS, 48, 48);
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);



}

//Output
void GameEngine::Reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
	//glDisable(GLU_CULLING);
    glMatrixMode (GL_PROJECTION); //set the matrix to projection
    glLoadIdentity ();
    gluPerspective (90.0, (GLfloat)w / (GLfloat)h, CAMERA_ZNEAR , CAMERA_ZFAR); //set the perspective (angle of sight, width, height, ,depth)
	glCullFace(GL_FRONT);
    glMatrixMode (GL_MODELVIEW); //set the matrix back to model
}

void GameEngine::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	Camera.Update( Player.GetX(), Player.GetY(), Player.GetZ());
	ang = fmod(ang+2,360);
	
	glDisable(GL_LIGHTING);

	glDisable(GL_DEPTH_TEST); //desactivo el depth test para que el jugador no vea como el skymap corta con el escenario
	sky.Draw(Data.GetID(IMG_SKYBOX), Player.GetX(), Player.GetY(), Player.GetZ());
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	//Scene.Draw(&Data, &ccShader, playerPos);
	if (drawPlanets) {
		sol.drawEarthAndMoon();
		sol.drawSun(&ccShader,glowOn);
		sol.drawAllPlanets();
		sol.drawSaturnRing();
		sol.CurrentEarthRotation += sol.EarthDayIncrement;
		sol.EarthDaysTranspired += sol.EarthDayIncrement;
	}
	//if (sol.particleFlag)
	if (drawParticles) {
		sol.drawAllParticles();
	}
	//glDepthMask(GL_TRUE);
	//glDisable(GL_BLEND);
	//glDisable(GL_LIGHTING);
	if (drawTerrain) {
		tg->draw(&Data, wireframeMode);
	}
	for (int i = 0; i < NUM_ASTEROIDS; i++)
	{
		//asteroidList[i].Draw(&Data);//,// &ccShader);
	}
	

	
	//if(abs(Camera.GetZ()) < Camera.GetDistance())
	//{
		//draw 
		
		Player.Draw(&Data,&Camera,&ccShader,glowOn);
	
	//}
	//else
	//{
		//draw 
		
		//Player.Draw(&Data, &Camera,  &ccShader);
		
	//}
	//glPopMatrix();
	//drawEarthAndMoon();
	
	
	
	//glLoadIdentity();
	if (drawWaterQ)
	{
		DrawWater();
	}
	//DrawSun();
	
	


	//if (EarthDaysTranspired == EARTH_ORBIT_DUR)
		//EarthDaysTranspired = 0;
	
	//drawAllParticles();

	glFlush();
	glutSwapBuffers();
}