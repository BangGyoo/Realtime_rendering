#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <string>
#include <vector>
#include "glm/gtx/string_cast.hpp"
#include "Loader.h"
#include "glm/glm.hpp"
#include "GL/glew.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class Object {

private:
	std::string path;
	GLuint vaoHandle;
	GLuint vbo_obj_vertices, vbo_obj_colors;
	GLuint ibo_obj_elements;
	

	int loadObj();
public:
	Object(std::string fileName) {
		path = fileName;
	}
	void draw();
	void setup();
};
