#pragma once


#include <iostream>
#include "GL/glew.h"
#include <string>
#include "Loader.h"


class MyGlWindow {
public:
	MyGlWindow(int w = 700, int h = 700);
	~MyGlWindow();
	void draw();
public:
	int m_width;
	int m_height;

	void setupBuffer();
	
};
