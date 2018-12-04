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
	glGenVertexArrays(1, &vaoHandle);	// �Ϲ��� c�� �迭 ����ص� ��������
	glBindVertexArray(vaoHandle);		// bind�� ����. Activate Ȥ�� ���� ���⿡ ���𰡸� �ҷ�.
										//glDrawArrays(GL_TRIANGLES, 0, 3);	// GL_TRIANGLES / GL_LINES / GL_POINTS �����ִ�
										//vbo ����
	glGenBuffers(1, &vbo_vlists);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vlists);	// vbo binding
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vlists.size() * 4, vlists.data(), GL_STATIC_DRAW);


	glVertexAttribPointer(
		0,		// attrib ��ȣ (0,1,....)
		4,		// �� vertex�� ����� ���� ��
		GL_FLOAT,			// type
		GL_FALSE,			// normalize �Ǿ��ִ��� Ȯ��
		0,//sizeof(float),					// stride : ��vertex���̿� ���� �ִ��� Ȯ��
		0					// offset : ���� �����ͷκ����� ��
	);
	glEnableVertexAttribArray(0);			// vbo ����
											// �� �Լ� ���� GPU���� ������ �ȴ�. �ѹ� �־��ָ� ������x
											// �������� �͵��� static �ᵵ ����
	glGenBuffers(1, &vbo_clists);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_clists);	// vbo binding
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*clists.size() * 3, clists.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(
		1,		// attrib ��ȣ (0,1,....)
		3,		// �� vertex�� ����� ���� ��
		GL_FLOAT,			// type
		GL_FALSE,			// normalize �Ǿ��ִ��� Ȯ��
		0,					// stride : ��vertex���̿� ���� �ִ��� Ȯ��
		0				// offset : ���� �����ͷκ����� ��
	);
	glEnableVertexAttribArray(1);			// vbo ����

											//glEnableVertexAttribArray(2);

	glBindVertexArray(0);		// vao����, �ش� �Լ��� 0�� ������ ���� unbind �ȴ�.



}

void checkeredFloor::draw()
{
	int size;
	glBindVertexArray(vaoHandle);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawArrays(GL_TRIANGLES, 0, 20000);
}
