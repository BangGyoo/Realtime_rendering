#include "global.h"

namespace global
{
	glm::vec4 lightPos = glm::vec4(50, 50, 50, 1); //glm::vec3 lightPos = glm::vec3(0, 10, 0);
	glm::vec3 Ia = glm::vec3(0.9, 0.9, 0.9); //(0.1, 0.1, 0.1); //Ambient Light Color
	glm::vec3 Id = glm::vec3(0.9, 0.9, 0.9); //(0.5, 0.5, 0.5); //Diffuse Light Color
	glm::vec3 Is = glm::vec3(0.9, 0.9, 0.9); //(0.2, 0.2, 0.2); //Specular Light Color

	glm::vec3 Ka(0.1, 0.1, 0.1); //Ambient Object Color
	glm::vec3 Kd(1, 1, 0); //Diffuse Object Color
	glm::vec3 Ks(1, 1, 0); //Specular Object Color
	GLfloat shiness = 10; //하이라이트 강한 이유인듯

	glm::vec3 backGround = glm::vec3(0.2, 0.2, 0.2);
	glm::vec2 floorSize = glm::vec2(10, 5); //ivec = int //그냥 glm::vec2면 float인 듯?
}
