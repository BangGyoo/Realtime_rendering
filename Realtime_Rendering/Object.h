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
	float obj_size;
	glm::vec3 obj_pos;

	int loadObj();
public:
	Object(std::string fileName, glm::vec3 pos = { 0,0,0 } , float size = 1.0f) {
		path = fileName;
		obj_size = size;
		obj_pos = pos;
	}
	void draw();
	void setup();
};
