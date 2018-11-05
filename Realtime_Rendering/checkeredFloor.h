#pragma once
#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <string>
#include "GL/glew.h"
#include <vector>
#include "Loader.h"
#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"

class checkeredFloor
{

private:
	float floorColor1[3];
	float floorColor2[3];
	float height;
	GLuint vaoHandle;
	GLuint vbo_vlists, vbo_clists;

public:
	void draw();
	void setup(float size=10, int nSquares=10);
	checkeredFloor(glm::vec3 color1, glm::vec3 color2, float height);
	
};