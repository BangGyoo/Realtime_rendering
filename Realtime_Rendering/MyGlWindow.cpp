
#include "MyGlWindow.h"

ShaderProgram *shaderProgram;
ShaderProgram *noLight;
ShaderProgram *teapot;

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

void MyGlWindow::initialize()
{
	m_cube = new ColorCube();
	m_checkeredFloor = new checkeredFloor(glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1.0f, 1.0f, 1.0f),-1.0f);
	//m_object = new Object("teapot_my.obj",glm::vec3(0,1,-0.1),0.1f);
	m_Sphere = new Sphere(3.0f, 60, 60);
	m_teapot = new VBOTeapot(64,glm::mat4(1.0f));
}

MyGlWindow::MyGlWindow(int w, int h)
{
	m_width = w;
	m_height = h;
	m_cube = NULL;

	glm::vec3 viewPoint(DEFAULT_VIEW_POINT[0], DEFAULT_VIEW_POINT[1], DEFAULT_VIEW_POINT[2]);
	glm::vec3 viewCenter(DEFAULT_VIEW_CENTER[0], DEFAULT_VIEW_CENTER[1], DEFAULT_VIEW_CENTER[2]);
	glm::vec3 upVector(DEFAULT_UP_VECTOR[0], DEFAULT_UP_VECTOR[1], DEFAULT_UP_VECTOR[2]);
	

	float aspect = (w / (float)h);
	m_viewer = new Viewer(viewPoint, viewCenter, upVector, 50.0f, aspect);



	initialize();
	setupBuffer();
}
MyGlWindow::~MyGlWindow() {

}
glm::vec3 eye;
glm::vec3 look;
glm::vec3 up;
glm::mat4 view;
glm::mat4 projection;
glm::mat4 modelview; glm::mat4 teapotModelView;
glm::mat4 inverseModelView; glm::mat4 teapotInverseModelView;
glm::mat3 normalMatrix; glm::mat3 taepotNormalMat;

void MyGlWindow::draw() {
	eye = m_viewer->getViewPoint();
	look = m_viewer->getViewCenter();
	up = m_viewer->getUpVector();
	view = glm::lookAt(eye, look, up);

	projection = perspective(m_viewer->getFieldOfView(),
		m_viewer->getAspectRatio(), 0.01f, 500.0f);  //projection matrix
	glm::mat4 model(1.0);
	glm::mat4 teapotModel = glm::translate(glm::mat4(1.f),glm::vec3(0,-1,0))
		* glm::scale(glm::mat4(1.f),glm::vec3(0.5,0.5,0.5))
		* glm::rotate(model, 90.0f, vec3(-1, -1, -1));

	////////////////////////// ModelView matrix		/////////////
	modelview = view * model; teapotModelView = view * teapotModel;
	inverseModelView = glm::inverse(modelview); teapotInverseModelView = glm::inverse(teapotModelView);
	normalMatrix = glm::mat3(glm::transpose(inverseModelView));
	taepotNormalMat = glm::mat3(glm::transpose(teapotInverseModelView));
	
	mvp = projection * view * model;

	glm::vec4 lightPos(50, 50, 50, 1);
	glm::vec3 Kd(0.7, 0.7, 0.0);
	glm::vec3 Id(0.9, 0.9, 0.9);


	shaderProgram->use();
	
	
	glUniform4fv(shaderProgram->uniform("LightLocation"),
		1, glm::value_ptr(lightPos));
	glUniform3fv(shaderProgram->uniform("Kd"),
		1, glm::value_ptr(Kd));
	glUniform3fv(shaderProgram->uniform("Id"),
		1, glm::value_ptr(Id));
	
	glUniformMatrix4fv(shaderProgram->uniform("ModelViewMatrix"),
		1, GL_FALSE, glm::value_ptr(modelview));  //modelView
	glUniformMatrix3fv(shaderProgram->uniform("NormalMatrix"),
		1, GL_FALSE, glm::value_ptr(normalMatrix));  //normalMatrix

	glUniformMatrix4fv(shaderProgram->uniform("MVP"),
		1, GL_FALSE, glm::value_ptr(mvp));
	
	if (m_Sphere) m_Sphere->draw();
	if (m_cube) m_cube->draw();

	shaderProgram->disable();
	
	noLight->use();

	glUniformMatrix4fv(noLight->uniform("MVP"),
		1, GL_FALSE, glm::value_ptr(mvp));

	if (m_checkeredFloor) m_checkeredFloor->draw();

	noLight->disable();
	
	mvp = projection * view * teapotModel;
	teapot->use();
	
	glUniform4fv(teapot->uniform("LightLocation"),
		1, glm::value_ptr(lightPos));
	glUniform3fv(teapot->uniform("Kd"),
		1, glm::value_ptr(Kd));
	glUniform3fv(teapot->uniform("Id"),
		1, glm::value_ptr(Id));

	glUniformMatrix4fv(teapot->uniform("ModelViewMatrix"),
		1, GL_FALSE, glm::value_ptr(teapotModelView));  //modelView
	glUniformMatrix3fv(teapot->uniform("NormalMatrix"),
		1, GL_FALSE, glm::value_ptr(taepotNormalMat));  //normalMatrix

	glUniformMatrix4fv(teapot->uniform("MVP"),
		1, GL_FALSE, glm::value_ptr(mvp));
	if (m_teapot) m_teapot->draw();
	teapot->disable();

	
}					


void MyGlWindow::setupBuffer() {		

	shaderProgram = new ShaderProgram();
	noLight = new ShaderProgram();
	teapot = new ShaderProgram();
	shaderProgram->initFromFiles("simple.vert", "simple.frag");
	noLight->initFromFiles("noLight.vert", "noLight.frag");
	teapot->initFromFiles("teapot.vert", "teapot.frag");

	shaderProgram->addUniform("LightLocation");
	shaderProgram->addUniform("Kd");
	shaderProgram->addUniform("Id");
	shaderProgram->addUniform("ModelViewMatrix");
	shaderProgram->addUniform("NormalMatrix");
	shaderProgram->addUniform("MVP");

	noLight->addUniform("MVP");

	teapot->addUniform("LightLocation");
	teapot->addUniform("Kd");
	teapot->addUniform("Id");
	teapot->addUniform("ModelViewMatrix");
	teapot->addUniform("NormalMatrix");
	teapot->addUniform("MVP");

	
	m_cube->setup();
	m_Sphere->setup();
	m_checkeredFloor->setup();
	m_teapot->setup();
	//m_object->setup();
	
}

