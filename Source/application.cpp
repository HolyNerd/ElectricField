
#include <application.h>
#include <chrono>
#include <iostream>

#define HIGH_QUALITY

Application::Application() {
	glfwInit();
	gl3wInit();	

	shaderPath = "/home/holynerd/Desktop/Projects/ElectricField/Shaders/";	
	window = glfwCreateWindow(800, 800, "OpenGL: Electric Field", NULL, NULL);
	glfwMakeContextCurrent(window);

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

	electricField.addCharge(-3.0, glm::vec2(-0.2, 0.0));	
	electricField.addCharge( 3.0, glm::vec2(-0.1, 0.0));	
	electricField.addCharge( 3.0, glm::vec2(-0.0, 0.0));	
	electricField.addCharge(-3.0, glm::vec2( 0.1, 0.0));	

	electricField.createLines();

}

void Application::display() {

	glfwMakeContextCurrent(window);
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
