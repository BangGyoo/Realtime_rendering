#include "Sphere.h"

#include <glm//gtc/constants.hpp>
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>


std::vector<glm::vec4> sphere_vertices;
std::vector<glm::vec3> sphere_normals;

Sphere::Sphere()
{

}


Sphere::~Sphere()
{
}



Sphere::Sphere(float rad, GLuint sl, GLuint st) :
	radius(rad), slices(sl), stacks(st)
{




	nVerts = (slices + 1) * (stacks + 1);
	elements = (slices * 2 * (stacks - 1)) * 3;

	// Verts
	float *v = new float[3 * nVerts];
	// Normals
	float * n = new float[3 * nVerts];
	// Tex coords
	float * tex = new float[2 * nVerts];    //we don't use it now
											// Index
	unsigned int * el = new unsigned int[elements];  //index

													 // Generate the vertex data
	generateVerts(v, n, tex, el);

	for (int i = 0; i < elements; i++) {
		sphere_vertices.push_back(glm::vec4(v[3 * el[i]] / 3, v[3 * el[i] + 1] / 3 + 2, v[3 * el[i] + 2] / 3, 1.0f));
	}
	for (int i = 0; i < elements; i++) {
		sphere_normals.push_back(glm::vec3(n[3 * el[i]], n[3 * el[i] + 1], n[3 * el[i] + 2]));
	}

	//create vao, vbo and ibo here... (We didn't use std::vector here...)


	delete[] v;
	delete[] n;
	delete[] el;
	delete[] tex;

}

void Sphere::draw()
{
	//glBindVertexArray(vaoHandle);
	//int size;
	//glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	//glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	//glBindVertexArray(0);
	int size;
	glBindVertexArray(vaoHandle);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawArrays(GL_TRIANGLES, 0, size*4);
}

void Sphere::generateVerts(float * verts, float * norms, float * tex,
	unsigned int * el)
{
	// Generate positions and normals
	GLfloat theta, phi;
	GLfloat thetaFac = glm::two_pi<float>() / slices;
	GLfloat phiFac = glm::pi<float>() / stacks;
	GLfloat nx, ny, nz, s, t;
	GLuint idx = 0, tIdx = 0;
	for (GLuint i = 0; i <= slices; i++) {
		theta = i * thetaFac;
		s = (GLfloat)i / slices;
		for (GLuint j = 0; j <= stacks; j++) {
			phi = j * phiFac;
			t = (GLfloat)j / stacks;
			nx = sinf(phi) * cosf(theta);
			ny = sinf(phi) * sinf(theta);
			nz = cosf(phi);
			verts[idx] = radius * nx; verts[idx + 1] = radius * ny; verts[idx + 2] = radius * nz;
			norms[idx] = nx; norms[idx + 1] = ny; norms[idx + 2] = nz;
			idx += 3;

			tex[tIdx] = s;
			tex[tIdx + 1] = t;
			tIdx += 2;
		}
	}

	// Generate the element list
	idx = 0;
	for (GLuint i = 0; i < slices; i++) {
		GLuint stackStart = i * (stacks + 1);
		GLuint nextStackStart = (i + 1) * (stacks + 1);
		for (GLuint j = 0; j < stacks; j++) {
			if (j == 0) {
				el[idx] = stackStart;
				el[idx + 1] = stackStart + 1;
				el[idx + 2] = nextStackStart + 1;
				idx += 3;
			}
			else if (j == stacks - 1) {
				el[idx] = stackStart + j;
				el[idx + 1] = stackStart + j + 1;
				el[idx + 2] = nextStackStart + j;
				idx += 3;
			}
			else {
				el[idx] = stackStart + j;
				el[idx + 1] = stackStart + j + 1;
				el[idx + 2] = nextStackStart + j + 1;
				el[idx + 3] = nextStackStart + j;
				el[idx + 4] = stackStart + j;
				el[idx + 5] = nextStackStart + j + 1;
				idx += 6;
			}
		}
	}
}

void Sphere::setup() {

	glGenVertexArrays(1, &vaoHandle);	// 일반적 c의 배열 사용해도 ㄱㅊㄱㅊ
	glBindVertexArray(vaoHandle);		// bind란 뭘까. Activate 혹은 나는 여기에 무언가를 할래.
										//glDrawArrays(GL_TRIANGLES, 0, 3);	// GL_TRIANGLES / GL_LINES / GL_POINTS 세개있다
										//vbo 생성
	glGenBuffers(1, &VBO_position);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position);	// vbo binding
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* sphere_vertices.size() * 4, sphere_vertices.data(), GL_STATIC_DRAW);


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

	glGenBuffers(1, &VBO_normal);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_normal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*sphere_normals.size() * 3, sphere_normals.data(), GL_STATIC_DRAW);
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

int Sphere::getVertexArrayHandle()
{
	return this->vaoHandle;
}