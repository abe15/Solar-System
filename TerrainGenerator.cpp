#include "TerrainGenerator.h"
#include "tables.h"

using namespace glm;

/*
	Constructor. Set variables.
*/
TerrainGenerator::TerrainGenerator(int num, float res,int shader){
	num_cells = num;
	cell_size = res;
	target = -5.0f;
	verts =  std::vector<vec3>();
	indices =std::vector<GLuint>();
	shaderProgram = shader;
}

/*
	Destructor. Clear vertices.
*/
TerrainGenerator::~TerrainGenerator(){
	verts.clear();
}

/*
	Renders terrain.
*/
void TerrainGenerator::draw(Data *Data, int choose) {

	if(!choose)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}	
	/*
	int k = indices.size();
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	//glColor3f(1, 0, 0);
	glDrawElements(GL_TRIANGLES,k, GL_UNSIGNED_INT, nullptr);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
	glUseProgram(0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);*/
	/*
	glUseProgram(shaderProgram);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(vec3), 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glColor3f(1, 0, 0);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);*/
	
	
	
	glEnable(GL_TEXTURE_2D);//, Data->GetID(IMG_GRASS));
	glBindTexture(GL_TEXTURE_2D, Data->GetID(IMG_GRASS));
	glColor3f(1.0f, 0,0);
	glBegin(GL_TRIANGLES);
	
	for (int i = 0; i < verts.size(); i++){
		
		
		
			
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(verts[i][0], verts[i][1]*100.0, verts[i][2]);

	}
	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(1.0f, 1.0f, 1.0f);
	//glFlush();
	
	}

/*
	Initializes other variables and the noise map, then runs algorithm.
*/
void TerrainGenerator::init(){
//	start[0] = 0;
	//start[1] = 0;//start[0];
	//start[2] = 0;//start[0];
	verts.clear();
	//generate noise map and run algorithm
	init_noise_map(start);
	MarchingCubes();
	setUpBuffer();
}
void TerrainGenerator::setUpBuffer()
{
	int k = verts.size();
	for (int i = 0; i < k;i++)
	{
		indices.push_back(i);
		
		
	}
	/*
	for (int r = 0; r < num_cells; ++r) {
		for (int c = 0; c < num_cells; ++c) {
			indices.push_back(r * num_cells + c);
			indices.push_back(r * num_cells + (c + 1));
			indices.push_back((r + 1)*num_cells + c);

			indices.push_back((r + 1) * num_cells + c);
			indices.push_back((r * num_cells + (c + 1)));
			indices.push_back((r + 1) * num_cells + (c + 1));
		}
	}
	*/
	/*
	// Create array object and buffers. Remember to delete your buffers when the object is destroyed!
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	

	// Bind the Vertex Array Object (VAO) first, then bind the associated buffers to it.
	// Consider the VAO as a container for all your buffers.
	glBindVertexArray(VAO);

	// Now bind a VBO to it as a GL_ARRAY_BUFFER. The GL_ARRAY_BUFFER is an array containing relevant data to what
	// you want to draw, such as vertices, normals, colors, etc.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// glBufferData populates the most recently bound buffer with data starting at the 3rd argument and ending after
	// the 2nd argument number of indices. How does OpenGL know how long an index spans? Go to glVertexAttribPointer
	//
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*verts.size(), &verts[0], GL_STATIC_DRAW);
	//glVertexPointer(3, GL_FLOAT, sizeof(vec3), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*indices.size(), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);*/
}
/*
	Sets the cell size. Bad name, I know.
*/
void TerrainGenerator::setCellSize(float s){
	if (cell_size != s)
		cell_size = s;
}

/*
	Runs the algorithm over the entire cell grid.
*/
void TerrainGenerator::MarchingCubes(){

	verts.clear();
	indices.clear();

	//iterate over the grid, running algorithm on each cube.
	
	for (int x = 0; x < num_cells; x++){
		
		for (int y = 0; y < num_cells; y++){
			for (int z = 0; z < num_cells; z++){
				vec3 p;
				p[0] = start[0] + x * cell_size;
				p[1] = start[1] + y * cell_size;
				p[2] = start[2] + z * cell_size;

				march_cube(p);
			}
		}
	}

}

/*
	Sets the seed values.
*/
void TerrainGenerator::setSeed(float a, float b, float c, float d){
	//set x sample ranges
	if (a < b){
		seeds[0] = a;
		seeds[1] = b;
	}
	else{
		seeds[0] = b;
		seeds[1] = a;
	}

	//set y sample ranges
	if (c < d){
		seeds[2] = c;
		seeds[3] = d;
	}
	else{
		seeds[2] = d;
		seeds[3] = c;
	}
	//verts.clear();
	//init();
}

/*
	Sample the noise map at a given point.
*/
float TerrainGenerator::sample(vec3 p){
	//get height at the given point
	return (map.GetValue(p[0], p[2])) - p[1];
}

/*
	Run the algorithm for a given cube with the bottom, front, left vertex at p.
*/
void TerrainGenerator::march_cube(vec3 p){
	float cube_value[8];
	vec3 edge_vertex[12];

	//get value at corners of cube.
	for (int vertex = 0; vertex < 8; vertex++){

		//temp represents the current corner. 
		//it takes the value of the starting point, p, plus the current
		//offset as given by the offsets table in tables.h
		vec3 temp = vec3(
			p[0] + offsets[vertex][0] * cell_size,
			p[1] + offsets[vertex][1] * cell_size,
			p[2] + offsets[vertex][2] * cell_size
		);

		//sample
		cube_value[vertex] = sample(temp);
	}

	//determine edge table index based on values at corners
	int index = 0;
	for (int test = 0; test < 8; test++){
		if (cube_value[test] > target){
			index |= 1 << test;
		}
	}

	int edgeFlags = edge_table[index];
	
	//if edgeFlags is 0, there are no faces in this cube
	if (edgeFlags == 0)
		return;

	//this loop determines if a given edge of the cube should contain a vertex and,
	//if so, the position of that vertex.
	float offset = 0;
	for (int edge = 0; edge < 12; edge++){
		if (edgeFlags & (1 << edge)){
			offset = get_offset(cube_value[edge_connection[edge][0]],
				cube_value[edge_connection[edge][1]]);

			edge_vertex[edge][0] = p[0] + (offsets[edge_connection[edge][0]][0]
				+ offset * edge_direction[edge][0]) * cell_size;
			edge_vertex[edge][1] = p[1] + (offsets[edge_connection[edge][0]][1]
				+ offset * edge_direction[edge][1]) * cell_size;
			edge_vertex[edge][2] = p[2] + (offsets[edge_connection[edge][0]][2]
				+ offset * edge_direction[edge][2]) * cell_size;
		}
	}

	//Based on the triangle table in tables.h, determine which of our
	//place our generated vertices in the vertex vector in the proper order.
	//iterating up to 5 because there will only ever be a maximum of 5
	//triangles in a given cube.
	for (int tri = 0; tri < 5; tri++){

		//if we reach a negative number, we have already found all
		//of our triangles.
		if (triTable[index][3 * tri] < 0)
			break;

		//add the 3 vertices of the triangle.
		for (int corner = 0; corner < 3; corner++){
			int vert = triTable[index][3 * tri + corner];

			verts.push_back(edge_vertex[vert]);
		}
	}
}

/*
	Generate the noise map.

	For more info on the functions/objects used here, check the
	libnoise documentation. They've got some cool stuff over there.
*/
void TerrainGenerator::init_noise_map(vec3 p){
	//create a perlin module and a noise map builder.
	module::Perlin mod;
	utils::NoiseMapBuilderPlane builder;

	//set the builder's source and destination
	builder.SetSourceModule(mod);
	builder.SetDestNoiseMap(map);

	//the noise map should be the same dimensions (x and z) as our
	//grid.
	builder.SetDestSize(num_cells, num_cells);

	//set sampling ranges
	builder.SetBounds(seeds[0], seeds[1], seeds[2], seeds[3]);

	//generate that stuff, boi.
	builder.Build();
}

/*
	Get the offset between two values.
*/
float TerrainGenerator::get_offset(float a, float b){
	double d = b - a;

	//are these points the same?
	//if so, return 0.5
	if (d == 0.0)
		return 0.5;

	return (target - a) / d;
}