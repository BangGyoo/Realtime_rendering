
#include "MyGlWindow.h"

ShaderProgram *shaderProgram;

void MyGlWindow::initialize()
{
	m_cube = new ColorCube();
}

MyGlWindow::MyGlWindow(int w, int h)
{
	m_width = w;
	m_height = h;

	initialize();
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// ���� Ŭ����
								// �÷����۴� ���۴� 2���� �Ӹ�(?) 800 * 800 �÷��� ���ϳ� �÷�����
								// ����ŷ ���۵� ������ �� ������� �ʴ´�.
								// �𽺹��۴� ����� ������Ʈ �Ÿ����� �����ϴ� ��Ʈ�÷���
								// ����Ʈ ���� ���� ������

	glViewport(0, 0, m_width, m_height);	// ���ϴ����� �׸� , ������ �� ��
	// ���̴� ȣ���ؼ� ���
	shaderProgram->use();
										// triangle���� ������ ���ؽ��� ù��° �̾��ش�!
										// GL_TRIANGLES�� �ϸ� �簢�� �׸��� 2���� �ﰢ�� 6���� vertex�� �����ؾ���
										// GL_STRIP�� �ڵ����� �̾��ش�. 4���� vertex�� �൵ ��
	
	if (m_cube) m_cube->draw();
	shaderProgram->disable();

}								
void MyGlWindow::setupBuffer() {		
	shaderProgram = new ShaderProgram();
	shaderProgram->initFromFiles("simple.vert", "simple.frag");
	
	m_cube->setup();
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

