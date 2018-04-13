#pragma comment(lib,"glew32")

#include <iostream>

#ifndef _GLOBALS_H



#define GLFW_INCLUDE_GLEXT

#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <list>
#include <algorithm>
#include <utility>
#include <fstream>
#include <string>
#include <GL/glut.h>

#define PI 3.14159265358979323846f


#endif // !_GLOBALS_H