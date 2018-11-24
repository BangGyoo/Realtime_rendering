#include "ColorCube.h"


std::vector<glm::vec4> cube_vertices;
std::vector<glm::vec3> cube_normals;

glm::vec3 computeNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
	glm::vec3 normal_vector = glm::cross(p2 - p1, p3 - p1);

	return glm::normalize(normal_vector);
}


void ColorCube::setup()  //Call from constructor
{

	GLfloat cube_vertice[] = {
		// front
		-1.0, -1.0, 1.0,
		1.0, -1.0, 1.0,
		1.0, 1.0, 1.0,
		-1.0, 1.0, 1.0,
		// back
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0, 1.0, -1.0,
		-1.0, 1.0, -1.0,
	};
	GLushort cube_elements[] = {
		0, 1, 2,		2, 3, 0,		1, 5, 6,
		6, 2, 1,		7, 6, 5,		5, 4, 7,
		4, 0, 3,		3, 7, 4,		4, 5, 1,
		1, 0, 4,		3, 2, 6,		6, 7, 3,
	};

	for (int i = 0; i < 36; i++) {
		cube_vertices.push_back(
			glm::vec4(cube_vertice[3*cube_elements[i]] -3.0f,
						cube_vertice[3*cube_elements[i]+1],
						cube_vertice[3*cube_elements[i]+2], 1.0f));
	}
	

	for (int i = 0; i < 12; i++) {
		glm::vec3 a(cube_vertices[3*i]);
		glm::vec3 b(cube_vertices[3*i + 1]);
		glm::vec3 c(cube_vertices[3*i + 2]);
		glm::vec3 normal_vec = computeNormal(a, b, c);
		cube_normals.push_back(normal_vec);
		cube_normals.push_back(normal_vec);
		cube_normals.push_back(normal_vec);
	}
	


	glGenVertexArrays(1, &vaoHandle);	// 일반적 c의 배열 사용해도 ㄱㅊㄱㅊ
	glBindVertexArray(vaoHandle);		// bind란 뭘까. Activate 혹은 나는 여기에 무언가를 할래.
	//glDrawArrays(GL_TRIANGLES, 0, 3);	// GL_TRIANGLES / GL_LINES / GL_POINTS 세개있다
	//vbo 생성
	glGenBuffers(1, &vbo_cube_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);	// vbo binding
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*cube_vertices.size() * 4, cube_vertices.data(), GL_STATIC_DRAW);


	glVertexAttribPointer(
		0,		// attrib 번호 (0,1,....)
		4,		// 한 vertex당 사용한 값의 수
		GL_FLOAT,			// type
		GL_FALSE,			// normalize 되어있는지 확인
		0,//sizeof(float),					// stride : 한vertex사이에 갭이 있는지 확인
		(void*)0					// offset : 시작 포인터로부터의 갭
	);
	glEnableVertexAttribArray(0);			// vbo 종료
												// 이 함수 쓰면 GPU에서 잡히게 된다. 한번 넣어주면 변하지x
												// 어지간한 것들은 static 써도 무방

	glGenBuffers(1, &vbo_cube_normals);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_normals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*cube_normals.size() * 3, cube_normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(
		1,		// attrib 번호 (0,1,....)
		3,		// 한 vertex당 사용한 값의 수
		GL_FLOAT,			// type
		GL_FALSE,			// normalize 되어있는지 확인
		0,					// stride : 한vertex사이에 갭이 있는지 확인
		(void*)0				// offset : 시작 포인터로부터의 갭
	);
	glEnableVertexAttribArray(1);			// vbo 종료

	glBindVertexArray(0);		// vao종료, 해당 함수에 0을 넣으면 종료 unbind 된다.


}

void ColorCube::draw()
{
	//glBindVertexArray(vaoHandle);
	//int size;
	//glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	//glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	//glBindVertexArray(0);
	int size;
	glBindVertexArray(vaoHandle);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawArrays(GL_TRIANGLES, 0, size);
}

