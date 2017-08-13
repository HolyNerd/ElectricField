
#include <application.h>
#include <iostream>

#define HIGH_QUALITY

Application::Application() {
	glfwInit();
	gl3wInit();	

	shaderPath = "/home/holynerd/Desktop/Projects/ElectricField/Shaders/";	
	window = glfwCreateWindow(950, 950, "OpenGL: Electric Field", NULL, NULL);
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
	std::cout << "Init Start()\n";
	electricField.init();


	electricField.addCharge( 1.0f, glm::vec2( 0.1f, -0.2f));
	electricField.addCharge( 2.0f, glm::vec2( 0.0f, 0.5f));
	electricField.addCharge( 5.0f, glm::vec2( 0.5f, 0.2f));
	electricField.addCharge(-2.0f, glm::vec2( 0.0f,-0.2f));
	electricField.addCharge( 1.0f, glm::vec2( 0.2f, 0.0f));
	electricField.addCharge(-9.0f, glm::vec2( 0.9f, 0.9f));
	electricField.addCharge( 5.0f, glm::vec2( -0.6f, -0.5f));

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
