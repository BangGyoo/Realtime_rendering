#pragma once


#include <iostream>
#include "GL/glew.h"
#include <string>
#include "Loader.h"
#include "ColorCube.h"
#include "Viewer.h"
#include "glm/gtc/type_ptr.hpp"


class MyGlWindow {
public:
	MyGlWindow(int w = 700, int h = 700);
	~MyGlWindow();
	void draw();
public:
	int m_width;
	int m_height;
	ColorCube *m_cube;
	Viewer *m_viewer;
	glm::mat4 mvp;
	void setupBuffer();
	void initialize();
};
