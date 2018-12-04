#include "checkeredFloor.h"

checkeredFloor::checkeredFloor(glm::vec3 color1, glm::vec3 color2,float height) {
	floorColor1[0] = color1.r;
	floorColor1[1] = color1.g;
	floorColor1[2] = color1.b;
	floorColor2[0] = color2.r;
	floorColor2[1] = color2.g;
	floorColor2[2] = color2.b;
	this->height = height;
}
std::vector <glm::vec4> vlists;
std::vector <glm::vec3> clists;

void checkeredFloor::setup(float size, int nSquares )
{


	// parameters:
	float maxX = size / 2, maxY = size / 2;
	float minX = -size / 2, minY = -size / 2;

	int x, y, v[3], i;
	float xp, yp, xd, yd;
	v[2] = 0;
	xd = (maxX - minX) / ((float)nSquares);
	yd = (maxY - minY) / ((float)nSquares);


	for (x = 0, xp = minX; x < nSquares; x++, xp += xd) {
		for (y = 0, yp = minY, i = x; y < nSquares; y++, i++, yp += yd) {
			if (i % 2 == 1) {
				clists.push_back(glm::vec3(floorColor1[0], floorColor1[1], floorColor1[2]));
				clists.push_back(glm::vec3(floorColor1[0], floorColor1[1], floorColor1[2]));
				clists.push_back(glm::vec3(floorColor1[0], floorColor1[1], floorColor1[2]));
				clists.push_back(glm::vec3(floorColor1[0], floorColor1[1], floorColor1[2]));
				clists.push_back(glm::vec3(floorColor1[0], floorColor1[1], floorColor1[2]));
				clists.push_back(glm::vec3(floorColor1[0], floorColor1[1], floorColor1[2]));
			}
			else {
				clists.push_back(glm::vec3(floorColor2[0], floorColor2[1], floorColor2[2]));
				clists.push_back(glm::vec3(floorColor2[0], floorColor2[1], floorColor2[2]));
				clists.push_back(glm::vec3(floorColor2[0], floorColor2[1], floorColor2[2]));
				clists.push_back(glm::vec3(floorColor2[0], floorColor2[1], floorColor2[2]));
				clists.push_back(glm::vec3(floorColor2[0], floorColor2[1], floorColor2[2]));
				clists.push_back(glm::vec3(floorColor2[0], floorColor2[1], floorColor2[2]));

			}
			vlists.push_back(glm::vec4(xp, height, yp, 1));
			vlists.push_back(glm::vec4(xp, height, yp + yd, 1));
			vlists.push_back(glm::vec4(xp + xd, height, yp + yd, 1));

			vlists.push_back(glm::vec4(xp, height, yp, 1));
			vlists.push_back(glm::vec4(xp + xd, height, yp + yd, 1));
			vlists.push_back(glm::vec4(xp + xd, height, yp, 1));



		} // end of for j
	}// end of for
	glGenVertexArrays(1, &vaoHandle);	// 일반적 c의 배열 사용해도 ㄱㅊㄱㅊ
	glBindVertexArray(vaoHandle);		// bind란 뭘까. Activate 혹은 나는 여기에 무언가를 할래.
										//glDrawArrays(GL_TRIANGLES, 0, 3);	// GL_TRIANGLES / GL_LINES / GL_POINTS 세개있다
										//vbo 생성
	glGenBuffers(1, &vbo_vlists);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vlists);	// vbo binding
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vlists.size() * 4, vlists.data(), GL_STATIC_DRAW);


	glVertexAttribPointer(
		0,		// attrib 번호 (0,1,....)
		4,		// 한 vertex당 사용한 값의 수
		GL_FLOAT,			// type
		GL_FALSE,			// normalize 되어있는지 확인
		0,//sizeof(float),					// stride : 한vertex사이에 갭이 있는지 확인
		0					// offset : 시작 포인터로부터의 갭
	);
	glEnableVertexAttribArray(0);			// vbo 종료
											// 이 함수 쓰면 GPU에서 잡히게 된다. 한번 넣어주면 변하지x
											// 어지간한 것들은 static 써도 무방
	glGenBuffers(1, &vbo_clists);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_clists);	// vbo binding
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*clists.size() * 3, clists.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(
		1,		// attrib 번호 (0,1,....)
		3,		// 한 vertex당 사용한 값의 수
		GL_FLOAT,			// type
		GL_FALSE,			// normalize 되어있는지 확인
		0,					// stride : 한vertex사이에 갭이 있는지 확인
		0				// offset : 시작 포인터로부터의 갭
	);
	glEnableVertexAttribArray(1);			// vbo 종료

											//glEnableVertexAttribArray(2);

	glBindVertexArray(0);		// vao종료, 해당 함수에 0을 넣으면 종료 unbind 된다.



}

void checkeredFloor::draw()
{
	int size;
	glBindVertexArray(vaoHandle);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawArrays(GL_TRIANGLES, 0, 20000);
}
