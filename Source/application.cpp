
#include <application.h>
#include <chrono>
#include <iostream>

#include <line.h>
#include <button.h>

#define HIGH_QUALITY

Application::Application(GLFWwindow* win) 
	: window(win)
{
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

	button.setPosition(glm::vec2(-0.84, 0.9));
	button.setSize(0.2, 0.08);
	button.setButtonImage("/home/holynerd/Desktop/Projects/ElectricField/Media/add_button.png");
	button.setButtonName("Button1");
	gui.addButton(button);

	button.setPosition(glm::vec2(-0.84, 0.8));
	button.setSize(0.2, 0.08);
	button.setButtonImage("/home/holynerd/Desktop/Projects/ElectricField/Media/delete_button.png");
	button.setButtonName("Button2");
	gui.addButton(button);

	electricField.init();

	electricField.addCharge(-3, glm::vec2(0.0f, 0.0f));
	electricField.addCharge(2, glm::vec2(0.2f, 0.3f));

	electricField.createLines();

	gui.bindWindow(window);
}

void Application::display() {
	if(gui.isButtonPressed("Button1"))
		std::cout << "1\n";
	if(gui.isButtonPressed("Button2"))
		std::cout << "2\n";
	
	background.draw();
	electricField.drawLines();
	gui.display();
}

void Application::shutdown() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

GLFWwindow* Application::getWindow() const { 
	return window;
}
