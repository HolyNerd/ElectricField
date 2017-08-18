

#include <application.h>
#include <chrono>
#include <iostream>

#define TEST_02
#define HIGH_QUALITY

float value = 1.0f;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	value += xoffset + yoffset;
}

Application::Application() {
	// GLFW init
	glfwInit();
	window = glfwCreateWindow(900, 900, "OpenGL: Electric Field", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	// OpenGL init
	glewInit();

#ifdef HIGH_QUALITY
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_BLEND, GL_NICEST);
#endif
}

Application::~Application() {
	
}

void Application::init() {
	electricField.init();
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        std::cout << "RightClick\n";
}

void Application::display() {
	glfwMakeContextCurrent(window);

	static double xPos, yPos;
	static int width, height;
		
	glfwGetWindowSize(window, &width, &height);
	glfwGetCursorPos(window, &xPos, &yPos);
	
	float hxPos, hyPos;
	
	hxPos = (2.0f * xPos) / width - 1;
	hyPos = 1.0f - (2.0f * yPos) / height;
	
	electricField.clear();
	glfwSetScrollCallback(window, scroll_callback);

	electricField.addCharge(1, glm::vec2(-0.2, 0.2));
	electricField.addCharge(-2, glm::vec2(-0.2,-0.2));
	electricField.addCharge(3, glm::vec2( 0.2,-0.2));
	electricField.addCharge(-4, glm::vec2( 0.2, 0.2));
	electricField.addCharge(value, glm::vec2(hxPos, hyPos));
	
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	electricField.createLines();

	static glm::vec4 backgroundColor{0.92f, 0.92f, 0.92f, 1.0f};
	glClearBufferfv(GL_COLOR, 0, glm::value_ptr(backgroundColor));


	electricField.drawLines();
}

void Application::shutdown() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

GLFWwindow* Application::getWindow() const { 
	return window;
}
