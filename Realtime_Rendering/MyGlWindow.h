#pragma once


#include <iostream>
#include "GL/glew.h"
#include <string>
#include "Loader.h"
#include "ColorCube.h"


class MyGlWindow {
public:
	MyGlWindow(int w = 700, int h = 700);
	~MyGlWindow();
	void draw();
public:
	int m_width;
	int m_height;
	ColorCube *m_cube;

	void setupBuffer();
	void initialize();
};
