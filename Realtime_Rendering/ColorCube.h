#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <string>
#include <vector>
#include "glm/gtx/string_cast.hpp"
#include "Loader.h"
#include "glm/glm.hpp"
#include "GL/glew.h"

class ColorCube
{

private:

	GLuint vaoHandle;
	GLuint vbo_cube_vertices, vbo_cube_colors;
	GLuint vbo_cube_normals;
	GLuint ibo_cube_elements;

public:
	void draw();
	void setup();
};
