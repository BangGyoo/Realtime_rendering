#pragma once


#include <iostream>
#include "GL/glew.h"
#include <string>
#include "Loader.h"
#include "ColorCube.h"
#include "checkeredFloor.h"
#include "Object.h"
#include "Viewer.h"
#include "Sphere.h"
#include "glm/gtc/type_ptr.hpp"
#include "vboteapot.h"
#include "teapotdata.h"
#include "global.h"




class MyGlWindow {
public:
	MyGlWindow(int w = 700, int h = 700);
	~MyGlWindow();
	void draw();
public:
	int m_width;
	int m_height;
	ColorCube *m_cube;
	checkeredFloor *m_checkeredFloor;
	Object *m_object;
	Viewer *m_viewer;
	Sphere *m_Sphere;
	VBOTeapot *m_teapot;
	glm::mat4 mvp;
	void setupBuffer();
	void initialize();
};
