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

glm::mat4 perspective(float fovy, float aspect, float near, float far) {

	glm::mat4 result(
		1.0 / (aspect*tan(glm::radians(fovy / 2))), 0, 0, 0,
		0, 1.0 / tan(glm::radians(fovy / 2)), 0, 0,
		0, 0, -((far + near) / (far - near)), -1,
		0, 0, -((2 * far * near) / (far - near)), 0);
	return result;
}
namespace test{
	void PracticeGLM() {
		glm::vec3 v(1, 3, 4);
		glm::vec3 x = glm::normalize(v);
		std::cout << to_string(x) << std::endl;
	}

	void CalcProjection() {
		glm::vec3 v(1, 2, 3);
		glm::vec3 u(5, 10, 1);
		glm::vec3 result = glm::normalize(u) * glm::dot(v, glm::normalize(u));
		std::cout << glm::length(result) << std::endl << glm::length(v) << std::endl;
	}

	void CalcDistance() {
		glm::vec3 n(0, 1, 0);
		glm::vec3 p(1, 0, 1);
		glm::vec3 x(-3, 3, 2);

		glm::vec3 v = x - p;
		n = glm::normalize(n);
		float d = glm::dot(v, n);
		std::cout << (d) << std::endl;
	}

	void CalcCross() {
		glm::vec3 u(1, -2, -1);
		glm::vec3 v(-2, 4, 1);

		glm::vec3 result(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
		std::cout << glm::to_string(result) << std::endl;

		glm::vec3 result2 = glm::cross(u, v);
		std::cout << glm::to_string(result2) << std::endl;

	}
	void CalcTriArea() {
		glm::vec3 p1(1, 0, 0);
		glm::vec3 p2(1, 1, 0);
		glm::vec3 p3(-1, 0, 0);
		
		glm::vec3 v1 = p2 - p1;
		glm::vec3 v2 = p3 - p1;

		float area = 0.5f*glm::length(glm::cross(v1, v2));
		std::cout << area << std::endl;
	}
	void CalcNormalVector() {
		glm::vec3 p1(1, 0, 0);
		glm::vec3 p2(1, 1, 0);
		glm::vec3 p3(-1, 0, 0);

		glm::vec3 v1 = p2 - p1;
		glm::vec3 v2 = p3 - p1;

		std::cout << glm::to_string(glm::cross(glm::normalize(v1), glm::normalize(v2))) << std::endl;

	}
	void CalcMatrix() {
		glm::mat4 m1(1);
		/*m1[0] = { 1, 0, 0, 0 };
		m1[1] = { 0,1,0,0 };
		m1[2] = { 0,0,1,0 };
		m1[3] = { 0,0,0,1 };*/
		std::cout << to_string(m1) << std::endl;
		glm::mat2x4 m2;
		m2[0] = { 1,1,1,1 };
		m2[1] = { 1,1,1,1 };
		
		std::cout << to_string(m1*m2) << std::endl;

	}
	void CalcInverseMat() {
		glm::mat4 m(2);
		std::cout << glm::to_string(glm::inverse(m)) << std::endl;
	}
	void CalcMixFunc() {
		glm::vec3 v1(1, 0, 0);
		glm::vec3 v2(0, 1, 1);
		std::cout << glm::to_string(glm::mix(v1, v2, 0.7f)) << std::endl;
	}
	void CalcShearing() {
		glm::mat4 m(1);
	}
}


int main() {
	test::CalcMixFunc();

	system("pause");
	return 0;
	//glm::vec3 cameraPosition(5), cameraTarget(0);
	//glm::vec3 upVector(0,1,0);

	//glm::mat4 result = LookAt(cameraPosition, cameraTarget, upVector);
/*
	float W = 780;
	float H = 750;
	float FovY = 45.0f;
	float NearZ = 0.1f;
	float FarZ = 500.0f;

	float Aspect = W / H;
	glm::mat4 result = perspective(FovY, Aspect, NearZ, FarZ);


	std::cout << glm::to_string(result) << std::endl;

	system("pause");
	return 0;*/
}