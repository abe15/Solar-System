#ifndef _TERRAIN2
#define _TERRAIN2

#include <vector>
#include <glm/glm.hpp>
#include "noiseutils.h"
#include "Data.h"


class TerrainGenerator{
public:
	//constructor
	TerrainGenerator(int, float,int);

	//destructor
	~TerrainGenerator();
	
	GLuint VBO, VAO, EBO;
	//render terrain
	
	void draw(Data *Data,int choose);
	//set cell size
	void setCellSize(float);

	//execute algorithm
	void MarchingCubes();

	//initialize noise map and run algorithm
	void init();
	glm::vec3 start;
	//set seed values
	void setSeed(float, float, float, float);
	GLint shaderProgram;
	std::vector<GLuint> indices;

private:
	//number cells in grid
	int num_cells;

	//size of cells
	float cell_size;

	//targer value
	float target;

	float seeds[4];

	//noise map

	utils::NoiseMap map;
	
	//vertices that represent terrain
	std::vector<glm::vec3> verts;
	
	void setUpBuffer();
	//sample noise map at point
	float sample(glm::vec3);

	//perform algorithm on given cube
	void march_cube(glm::vec3);

	//initialize noise map
	void init_noise_map(glm::vec3);

	//get offset between two values
	float get_offset(float, float);
};
#endif