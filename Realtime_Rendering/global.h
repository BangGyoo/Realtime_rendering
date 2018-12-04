#pragma once

#include <glm/mat4x4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>

#include "MyGlWindow.h"

namespace global
{
	extern glm::vec4 lightPos;
	extern glm::vec3 Ia;
	extern glm::vec3 Id;
	extern glm::vec3 Is;

	extern glm::vec3 Ka;
	extern glm::vec3 Kd;
	extern glm::vec3 Ks;
	extern GLfloat shiness;

	extern glm::vec3 backGround;
	extern glm::vec2 floorSize; //extern glm::ivec2 floorSize; //ivec = int //그냥 glm::vec2면 float인 듯?
};

