
#include "NoLight.h"

ShaderProgram *shaderProgram;

static float DEFAULT_VIEW_POINT[3] = { 5, 5, 5 };
static float DEFAULT_VIEW_CENTER[3] = { 0, 0, 0 };
static float DEFAULT_UP_VECTOR[3] = { 0, 1, 0 };

glm::mat4 perspective(float fovy, float aspect, float near, float far) {

	glm::mat4 result(
		1.0 / (aspect*tan(glm::radians(fovy / 2))), 0, 0, 0,
		0, 1.0 / tan(glm::radians(fovy / 2)), 0, 0,
		0, 0, -((far + near) / (far - near)), -1,
		0, 0, -((2 * far * near) / (far - near)), 0);
	return result;
}

void NoLight::initialize()
{
	m_checkeredFloor = new checkeredFloor(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), -1.0f);
}

NoLight::NoLight(int w, int h)
{
	m_width = w;
	m_height = h;

	glm::vec3 viewPoint(DEFAULT_VIEW_POINT[0], DEFAULT_VIEW_POINT[1], DEFAULT_VIEW_POINT[2]);
	glm::vec3 viewCenter(DEFAULT_VIEW_CENTER[0], DEFAULT_VIEW_CENTER[1], DEFAULT_VIEW_CENTER[2]);
	glm::vec3 upVector(DEFAULT_UP_VECTOR[0], DEFAULT_UP_VECTOR[1], DEFAULT_UP_VECTOR[2]);


	float aspect = (w / (float)h);
	m_viewer = new Viewer(viewPoint, viewCenter, upVector, 60.0f, aspect);



	initialize();
	setupBuffer();
}
NoLight::~NoLight() {

}
void NoLight::draw() {
	glm::vec3 eye = m_viewer->getViewPoint();
	glm::vec3 look = m_viewer->getViewCenter();
	glm::vec3 up = m_viewer->getUpVector();
	glm::mat4 view = glm::lookAt(eye, look, up);


	glm::mat4 projection = perspective(m_viewer->getFieldOfView(),
		m_viewer->getAspectRatio(), 0.01f, 50.0f);  //projection matrix
	glm::mat4 model(1.0);

	static float x = 0;
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




	mvp = projection * view * model;

	glUniformMatrix4fv(shaderProgram->uniform("mvp"),
		1, GL_FALSE, glm::value_ptr(mvp));

	if (m_checkeredFloor) m_checkeredFloor->draw();

	shaderProgram->disable();




}


void NoLight::setupBuffer() {

	shaderProgram = new ShaderProgram();
	shaderProgram->initFromFiles("noLight.vert", "noLight.frag");


	shaderProgram->addUniform("mvp");


	m_checkeredFloor->setup();

}