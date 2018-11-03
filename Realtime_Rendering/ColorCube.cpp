#include "ColorCube.h"



void ColorCube::setup()  //Call from constructor
{

	GLfloat cube_vertices[] = {
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

	GLfloat cube_colors[] = {
		// front colors
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0,
		// back colors
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0,
	};

	GLushort cube_elements[] = {
		0, 1, 2,		2, 3, 0,		1, 5, 6,
		6, 2, 1,		7, 6, 5,		5, 4, 7,
		4, 0, 3,		3, 7, 4,		4, 5, 1,
		1, 0, 4,		3, 2, 6,		6, 7, 3,
	};
	
	glGenVertexArrays(1, &vaoHandle);	// 일반적 c의 배열 사용해도 ㄱㅊㄱㅊ
	glBindVertexArray(vaoHandle);		// bind란 뭘까. Activate 혹은 나는 여기에 무언가를 할래.
	glDrawArrays(GL_TRIANGLES, 0, 3);	// GL_TRIANGLES / GL_LINES / GL_POINTS 세개있다
	//vbo 생성
	glGenBuffers(1, &vbo_cube_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);	// vbo binding
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);


	glVertexAttribPointer(
		0,		// attrib 번호 (0,1,....)
		3,		// 한 vertex당 사용한 값의 수
		GL_FLOAT,			// type
		GL_FALSE,			// normalize 되어있는지 확인
		0,					// stride : 한vertex사이에 갭이 있는지 확인
		0					// offset : 시작 포인터로부터의 갭
	);
	glEnableVertexAttribArray(0);			// vbo 종료
												// 이 함수 쓰면 GPU에서 잡히게 된다. 한번 넣어주면 변하지x
												// 어지간한 것들은 static 써도 무방
	glGenBuffers(1, &vbo_cube_colors);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_colors);	// vbo binding
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);

	glVertexAttribPointer(
		1,		// attrib 번호 (0,1,....)
		3,		// 한 vertex당 사용한 값의 수
		GL_FLOAT,			// type
		GL_FALSE,			// normalize 되어있는지 확인
		0,					// stride : 한vertex사이에 갭이 있는지 확인
		0					// offset : 시작 포인터로부터의 갭
	);
	glEnableVertexAttribArray(1);			// vbo 종료

	glGenBuffers(1, &ibo_cube_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);

	glBindVertexArray(0);		// vao종료, 해당 함수에 0을 넣으면 종료 unbind 된다.

	

}

void ColorCube::draw()
{
	glBindVertexArray(vaoHandle);
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

