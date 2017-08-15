
#include <application.h>
#include <chrono>
#include <iostream>

#define HIGH_QUALITY

float value = 1.0f;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	value += xoffset + yoffset;
}

Application::Application() {
	glfwInit();

	shaderPath = "/home/holynerd/Desktop/Projects/ElectricField/Shaders/";	
	window = glfwCreateWindow(720, 720, "OpenGL: Electric Field", NULL, NULL);
	glfwMakeContextCurrent(window);

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
	electricField.addCharge( 3.0, glm::vec2(-0.2, 0.0));	
	electricField.addCharge( 4.0, glm::vec2( 0.2, 0.2));
	electricField.addCharge( 2.0, glm::vec2(-0.2, 0.6));
	electricField.addCharge( 1.0, glm::vec2(-0.1, -0.7));

	electricField.addCharge(value, glm::vec2(hxPos, hyPos));	

	electricField.createLines();

	static glm::vec4 backgroundColor{1.0f, 1.0f, 1.0f, 1.0f};
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


