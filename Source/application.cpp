
#include <application.h>
#include <iostream>

//#define HIGH_QUALITY

Application::Application() {
	glfwInit();
	gl3wInit();	

	shaderPath = "/home/holynerd/Desktop/Projects/ElectricField/Shaders/";	
	window = glfwCreateWindow(700, 700, "OpenGL: Electric Field", NULL, NULL);
	glfwMakeContextCurrent(window);
}

Application::~Application() {
}

void Application::init() {
	electricField.init();
	electricField.addCharge( 2.0f, glm::vec2( 0.2f,  0.0f));
	electricField.addCharge(-2.0f, glm::vec2(-0.2f,  0.0f));
	electricField.addCharge(-2.0f, glm::vec2(-0.3f,  0.3f));
	electricField.createLines();

#ifdef HIGH_QUALITY

	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#endif
}

void Application::display() {
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
