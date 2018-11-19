#pragma once
#include <iostream>
#include "GL/glew.h"
#include <string>
#include "Loader.h"
#include "checkeredFloor.h"
#include "Viewer.h"
#include "glm/gtc/type_ptr.hpp"



class NoLight {
public:
	NoLight(int w = 700, int h = 700);
	~NoLight();
	void draw();
public:
	int m_width;
	int m_height;
	checkeredFloor *m_checkeredFloor;
	Viewer *m_viewer;
	glm::mat4 mvp;
	void setupBuffer();
	void initialize();
};