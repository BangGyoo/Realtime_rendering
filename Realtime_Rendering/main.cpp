#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

int main() {

	glm::vec3 test(1, 2, 3);

	std::cout << glm::to_string(test) << std::endl;

	system("pause");
	return 0;
}