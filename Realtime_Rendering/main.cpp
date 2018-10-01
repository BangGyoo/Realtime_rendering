#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

glm::mat4 LookAt(glm::vec3 campos, glm::vec3 look, glm::vec3 up) {

	glm::mat4 rotate(1.0f);
	glm::vec3 Zc = glm::normalize(campos - look);
	glm::vec3 Xc = glm::normalize(glm::cross(up, Zc));
	glm::vec3 Yc = glm::normalize(glm::cross(Zc, Xc));
	rotate[0] = glm::vec4(Xc, 0);
	rotate[1] = glm::vec4(Yc, 0);
	rotate[2] = glm::vec4(Zc, 0);
	rotate = glm::transpose(rotate);

	glm::mat4 transfer(1.0f);
	transfer = glm::translate(transfer, -glm::vec3(5, 5, 5));

	glm::mat4 result = (rotate * transfer);
	//glm::transpose(result);
	return result;
}

int main() {

	glm::vec3 cameraPosition(5), cameraTarget(0);
	glm::vec3 upVector(0,1,0);

	glm::mat4 result = LookAt(cameraPosition, cameraTarget, upVector);

	std::cout << glm::to_string(result) << std::endl;

	system("pause");
	return 0;
}