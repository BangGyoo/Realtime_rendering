
#include "MyGlWindow.h"

ShaderProgram *shaderProgram;
GLuint vao;
GLuint vboPosition,vboColor;

MyGlWindow::MyGlWindow(int w, int h)
{
	m_width = w;
	m_height = h;

	setupBuffer();
}
MyGlWindow::~MyGlWindow() {

}
void MyGlWindow::draw() {
	static float x=0;
	if (x < 1.0f) {
		glClearColor(x, x, x, 1.0);
		x += 0.001f;
	}
	else x = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// 버퍼 클리어
								// 컬러버퍼는 버퍼는 2차원 머리(?) 800 * 800 컬러는 셀하나 컬러저장
								// 마스킹 버퍼도 있지만 잘 사용하진 않는다.
								// 댑스버퍼는 가까운 오브젝트 거리값을 측정하는 비트플래그
								// 디폴트 값은 따로 있을까

	glViewport(0, 0, m_width, m_height);	// 좌하단으로 그림 , 이유는 모름 ㅋ
	// 쉐이더 호출해서 사용
	shaderProgram->use();
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);	// GL_TRIANGLES / GL_LINES / GL_POINTS 세개있다.
										// triangle쓰면 마지막 버텍스와 첫번째 이어준다!
										// GL_TRIANGLES로 하면 사각형 그릴때 2개의 삼각형 6개의 vertex를 지정해야함
										// GL_STRIP는 자동으로 이어준다. 4개의 vertex만 줘도 됨
	shaderProgram->disable();

}								
void MyGlWindow::setupBuffer() {		
	shaderProgram = new ShaderProgram();
	shaderProgram->initFromFiles("simple.vert", "simple.frag");
	
	const float vertexPosition[] = {
		-0.2f, -0.2f, 0, 1.0f,
		0, 0.2f, 0, 1.0f,
		0.2f, -0.2f, 0, 1.0f			// vector는 0, 동차좌표계는 1
	};
	const float vertexColor[] = {
		1,0,0,
		0,1,0,
		0,0,1
	};
	
	glGenVertexArrays(1, &vao);	// 일반적 c의 배열 사용해도 ㄱㅊㄱㅊ
	glBindVertexArray(vao);		// bind란 뭘까. Activate 혹은 나는 여기에 무언가를 할래.
	//vbo 생성
	glGenBuffers(1, &vboPosition);
	glBindBuffer(GL_ARRAY_BUFFER, vboPosition);	// vbo binding
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*4*3,vertexPosition,GL_STATIC_DRAW);


	glVertexAttribPointer(
		0,		// attrib 번호 (0,1,....)
		4,		// 한 vertex당 사용한 값의 수
		GL_FLOAT,			// type
		GL_FALSE,			// normalize 되어있는지 확인
		0,					// stride : 한vertex사이에 갭이 있는지 확인
		0					// offset : 시작 포인터로부터의 갭
		);
	glEnableVertexAttribArray(0);			// vbo 종료
												// 이 함수 쓰면 GPU에서 잡히게 된다. 한번 넣어주면 변하지x
												// 어지간한 것들은 static 써도 무방
	glGenBuffers(1, &vboColor);
	glBindBuffer(GL_ARRAY_BUFFER, vboColor);	// vbo binding
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*3, vertexColor, GL_STATIC_DRAW);

	glVertexAttribPointer(
		1,		// attrib 번호 (0,1,....)
		3,		// 한 vertex당 사용한 값의 수
		GL_FLOAT,			// type
		GL_FALSE,			// normalize 되어있는지 확인
		0,					// stride : 한vertex사이에 갭이 있는지 확인
		0					// offset : 시작 포인터로부터의 갭
	);
	glEnableVertexAttribArray(1);			// vbo 종료

	glBindVertexArray(0);		// vao종료, 해당 함수에 0을 넣으면 종료 unbind 된다.
	//
	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);

	//struct vertexAttr {
	//	GLfloat posX, posY, posZ;
	//	GLfloat r, g, b;
	//};
	//
	//vertexAttr * verts = new vertexAttr[3];
	//verts[0].posX = -0.2f; verts[0].posY = -0.2f; verts[0].posZ = 0.0f;
	//verts[0].r = 1; verts[0].g = 0; verts[0].b = 0;
	//verts[1].posX = 0.0f; verts[1].posY = 0.2f; verts[1].posZ = 0.0f;
	//verts[1].r = 0; verts[1].g = 1; verts[1].b = 0;
	//verts[2].posX = 0.2f; verts[2].posY = -0.2f; verts[2].posZ = 0.0f;
	//verts[2].r = 0; verts[2].g = 0; verts[2].b = 1;

	//glGenBuffers(1, &vbo);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertexAttr) * 3, verts, GL_STATIC_DRAW);
	//glVertexAttribPointer(
	//	0,
	//	3,
	//	GL_FLOAT,
	//	GL_FALSE,
	//	sizeof(vertexAttr),
	//	(void *)0			// starting
	//);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(
	//	1,
	//	3,
	//	GL_FLOAT,
	//	GL_FALSE,
	//	sizeof(vertexAttr),
	//	(void *)(sizeof(float)*3)			// starting
	//);
	//glEnableVertexAttribArray(1);
	//
	//glBindVertexArray(0);
}

