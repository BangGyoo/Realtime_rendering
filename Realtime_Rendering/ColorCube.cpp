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
	
	glGenVertexArrays(1, &vaoHandle);	// �Ϲ��� c�� �迭 ����ص� ��������
	glBindVertexArray(vaoHandle);		// bind�� ����. Activate Ȥ�� ���� ���⿡ ���𰡸� �ҷ�.
	glDrawArrays(GL_TRIANGLES, 0, 3);	// GL_TRIANGLES / GL_LINES / GL_POINTS �����ִ�
	//vbo ����
	glGenBuffers(1, &vbo_cube_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);	// vbo binding
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);


	glVertexAttribPointer(
		0,		// attrib ��ȣ (0,1,....)
		3,		// �� vertex�� ����� ���� ��
		GL_FLOAT,			// type
		GL_FALSE,			// normalize �Ǿ��ִ��� Ȯ��
		0,					// stride : ��vertex���̿� ���� �ִ��� Ȯ��
		0					// offset : ���� �����ͷκ����� ��
	);
	glEnableVertexAttribArray(0);			// vbo ����
												// �� �Լ� ���� GPU���� ������ �ȴ�. �ѹ� �־��ָ� ������x
												// �������� �͵��� static �ᵵ ����
	glGenBuffers(1, &vbo_cube_colors);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_colors);	// vbo binding
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);

	glVertexAttribPointer(
		1,		// attrib ��ȣ (0,1,....)
		3,		// �� vertex�� ����� ���� ��
		GL_FLOAT,			// type
		GL_FALSE,			// normalize �Ǿ��ִ��� Ȯ��
		0,					// stride : ��vertex���̿� ���� �ִ��� Ȯ��
		0					// offset : ���� �����ͷκ����� ��
	);
	glEnableVertexAttribArray(1);			// vbo ����

	glGenBuffers(1, &ibo_cube_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);

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

