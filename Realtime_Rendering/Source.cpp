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

// ★★ glfw 먼저 glew 나중에 초기화 필수 ★★
// 쉐이더의 변수들을 공유하기 위해서 in/ out을 사용하고
// 버텍스와 플래그먼트 쉐이더는 필수 다른건 option
// GLSL은 신텍스 기능으로 거의 GLM과 비슷
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


	glfwSwapInterval(1);	//vsync. v싱크 만들어주는거 아무튼 좋음

	printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
	// 가급적이면 printf 쓰지마라 속도 犬느림

	glfwSetWindowSizeCallback(window, window_resize_callback);  //등록
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetKeyCallback(window, key_callback);
	

	//window_resize_callback(window, width, height);
	glfwSetWindowTitle(window, u8"나의 openGL윈도우");
	
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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// 버퍼 클리어
															// 컬러버퍼는 버퍼는 2차원 머리(?) 800 * 800 컬러는 셀하나 컬러저장
															// 마스킹 버퍼도 있지만 잘 사용하진 않는다.
															// 댑스버퍼는 가까운 오브젝트 거리값을 측정하는 비트플래그
															// 디폴트 값은 따로 있을까

		glViewport(0, 0, win->m_width, win->m_height);	// 좌하단으로 그림 , 이유는 모름 ㅋ
												// 쉐이더 호출해서 사용

		// 뭔가 해줌
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