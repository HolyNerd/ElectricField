
#include <application.h>
#include <chrono>
#include <iostream>

#include <line.h>

#define HIGH_QUALITY

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

	background.init();
	background.setRect(glm::vec2(0.0, 0.0), 2.0f, 2.0f);
	background.setTexture("/home/holynerd/Desktop/Projects/ElectricField/Media/background.png");
	background.setShader("/home/holynerd/Desktop/Projects/ElectricField/Shaders/background");
	background.update();
}

Application::~Application() {
}

void Application::init() {

	electricField.init();
	
}

void Application::display() {
	background.draw();
	
}

void Application::shutdown() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

GLFWwindow* Application::getWindow() const { 
	return window;
}
