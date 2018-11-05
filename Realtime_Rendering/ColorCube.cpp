#include "ColorCube.h"


std::vector<glm::vec4> cube_vertices;
std::vector<glm::vec3> cube_colors;

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

	for (int i = 0; i < 8; i++) {
		cube_vertices.push_back(glm::vec4(cube_vertice[3 * i], cube_vertice[3 * i +1], cube_vertice[3 * i +2], 1.0f));
	}

	GLfloat cube_color[] = {
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
	for (int i = 0; i < 8; i++) {
		cube_colors.push_back(glm::vec3(cube_color[3*i], cube_color[3*i + 1], cube_color[3*i + 2]));
	}
	
	GLushort cube_elements[] = {
		0, 1, 2,		2, 3, 0,		1, 5, 6,
		6, 2, 1,		7, 6, 5,		5, 4, 7,
		4, 0, 3,		3, 7, 4,		4, 5, 1,
		1, 0, 4,		3, 2, 6,		6, 7, 3,
	};


	glGenVertexArrays(1, &vaoHandle);	// �Ϲ��� c�� �迭 ����ص� ��������
	glBindVertexArray(vaoHandle);		// bind�� ����. Activate Ȥ�� ���� ���⿡ ���𰡸� �ҷ�.
	//glDrawArrays(GL_TRIANGLES, 0, 3);	// GL_TRIANGLES / GL_LINES / GL_POINTS �����ִ�
	//vbo ����
	glGenBuffers(1, &vbo_cube_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);	// vbo binding
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*cube_vertices.size() * 4, cube_vertices.data(), GL_STATIC_DRAW);


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
	glGenBuffers(1, &vbo_cube_colors);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_colors);	// vbo binding
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*cube_vertices.size() * 3, cube_colors.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(
		1,		// attrib ��ȣ (0,1,....)
		3,		// �� vertex�� ����� ���� ��
		GL_FLOAT,			// type
		GL_FALSE,			// normalize �Ǿ��ִ��� Ȯ��
		0,					// stride : ��vertex���̿� ���� �ִ��� Ȯ��
		0				// offset : ���� �����ͷκ����� ��
	);
	glEnableVertexAttribArray(1);			// vbo ����

	glGenBuffers(1, &ibo_cube_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);

	//glEnableVertexAttribArray(2);

	glBindVertexArray(0);		// vao����, �ش� �Լ��� 0�� ������ ���� unbind �ȴ�.

	

}

void ColorCube::draw()
{
	glBindVertexArray(vaoHandle);
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

