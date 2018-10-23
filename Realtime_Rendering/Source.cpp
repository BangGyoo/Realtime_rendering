#include "MyGlWindow.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

MyGlWindow *win;

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

	glfwSetKeyCallback(window, key_callback);  //���
	glfwSetWindowSizeCallback(window, window_resize_callback);  //���

	//window_resize_callback(window, width, height);
	glfwSetWindowTitle(window, u8"���� openGL������");
	
	win = new MyGlWindow(width,height);

	while (!glfwWindowShouldClose(window))
	{     //////////////////////////////

		

		// ���� ����
		win->draw();


		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();



	}


	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;



}