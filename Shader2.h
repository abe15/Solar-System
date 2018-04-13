#pragma once

#include "Globals.h"


#define NUM_PROGRAMS 6


enum {
	PROGRAM_SIMPLE_TERRAIN,
	PROGRAM_SIMPLE_LIGHTBEAM,
	PROGRAM_SIMPLE_LIGHTBALL,
	PROGRAM_COMPLEX_NORMALMAP_LAVAGLOW,
	PROGRAM_COMPLEX_NORMALMAP,
	PROGRAM_ASTEROID
};

class Shader2
{
public:
	Shader2();
	~Shader2();

	void Load();
	void Activate(int program_id);
	void Deactivate();

	template <class T>
	void SetUniform(char* uniform, T value)
	{
		GLint loc = glGetUniformLocation(programs[current_prog_id], uniform);
		if (loc != -1)
		{
			if(typeid(T) == typeid(int)) glUniform1i(loc, value);
			else glUniform1f(loc, value);
		}
	}
	GLint GetLocation(char* uniform){ return glGetUniformLocation(programs[current_prog_id], uniform);}

private:
	GLuint programs[NUM_PROGRAMS];
	int current_prog_id;
};
