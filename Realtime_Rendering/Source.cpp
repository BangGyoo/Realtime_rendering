#include "MyGlWindow.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

MyGlWindow *win;
bool lbutton_down;
bool rbutton_down;
bool mbutton_down;
double m_lastMouseX;
double m_lastMouseY;
double cx, cy;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		std::cout << " hello world ~ " << std::endl;
}
static void window_resize_callback(GLFWwindow * window, int width, int height) {
	win->m_width = width;
	win->m_height = height;


}
static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	cx = xpos;
	cy = ypos;
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		m_lastMouseX = xpos;
		m_lastMouseY = ypos;
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (GLFW_PRESS == action)
			lbutton_down = true;
		else if (GLFW_RELEASE == action)
			lbutton_down = false;
	}

	else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (GLFW_PRESS == action)
			rbutton_down = true;
		else if (GLFW_RELEASE == action)
			rbutton_down = false;
	}

	else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {

		if (GLFW_PRESS == action)
			mbutton_down = true;
		else if (GLFW_RELEASE == action)
			mbutton_down = false;
		
	}
}
void mouseDragging(double width, double height)
{


	if (lbutton_down) {
		float fractionChangeX = static_cast<float>(cx - m_lastMouseX) / static_cast<float>(width);
		float fractionChangeY = static_cast<float>(m_lastMouseY - cy) / static_cast<float>(height);
		win->m_viewer->rotate(fractionChangeX, fractionChangeY);
	}
	else if (mbutton_down) {
		float fractionChangeX = static_cast<float>(cx - m_lastMouseX) / static_cast<float>(width);
		float fractionChangeY = static_cast<float>(m_lastMouseY - cy) / static_cast<float>(height);
		win->m_viewer->zoom(fractionChangeY);
	}
	else if (rbutton_down) {
		float fractionChangeX = static_cast<float>(cx - m_lastMouseX) / static_cast<float>(width);
		float fractionChangeY = static_cast<float>(m_lastMouseY - cy) / static_cast<float>(height);
		win->m_viewer->translate(-fractionChangeX, -fractionChangeY, 1);
	}
	m_lastMouseX = cx;
	m_lastMouseY = cy;
}

// �ڡ� glfw ���� glew ���߿� �ʱ�ȭ �ʼ� �ڡ�
// ���̴��� �������� �����ϱ� ���ؼ� in/ out�� ����ϰ�
// ���ؽ��� �÷��׸�Ʈ ���̴��� �ʼ� �ٸ��� option
// GLSL�� ���ؽ� ������� ���� GLM�� ���
int main()
{


	if (!glfwInit())
	{
		// Initialization failed
		std::cout << "init error" << std::endl;
		return 0;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	int width = 800;
	int height = 800;
	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window;
	
	window = glfwCreateWindow(width, height, "OpenGL FrameWork", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}


	glfwMakeContextCurrent(window);
	/* Make the window's context current */
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		//Problem: glewInit failed, something is seriously wrong.
		std::cout << "glewInit failed, aborting." << std::endl;
		return 0;
	}


	glfwSwapInterval(1);	//vsync. v��ũ ������ִ°� �ƹ�ư ����

	printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
	// �������̸� printf �������� �ӵ� ̳����

	glfwSetWindowSizeCallback(window, window_resize_callback);  //���
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetKeyCallback(window, key_callback);
	

	//window_resize_callback(window, width, height);
	glfwSetWindowTitle(window, u8"���� openGL������");
	
	win = new MyGlWindow(width,height);
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{     //////////////////////////////

		
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

		glViewport(0, 0, win->m_width, win->m_height);	// ���ϴ����� �׸� , ������ �� ��
												// ���̴� ȣ���ؼ� ���

		// ���� ����
		win->draw();


		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();

		mouseDragging(win->m_width, win->m_height);

	}


	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;



}