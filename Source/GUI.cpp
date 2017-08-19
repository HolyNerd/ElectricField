
#include <GUI.h>
#include <iostream>

GUI::GUI() {

}

GUI::~GUI() {

}

bool GUI::isButtonPressed(std::string buttonName) {
	glm::vec2 mousePosition = getMousePosition();

	if(GUI::_mouse_button_pressed == true) {
		for(Button& button : _buttons) {
			if(button.getName() == buttonName && button.isIn(mousePosition)) 
				return true;
		}		
		return false;
	}
}

bool GUI::_mouse_button_pressed = false;

const glm::vec2 GUI::getMousePosition() {
	int winWidth, winHeight;
	double cursorxPos, cursoryPos;
	
	glfwGetWindowSize(window, &winWidth, &winHeight);
	glfwGetCursorPos(window, &cursorxPos, &cursoryPos);

	cursorxPos = (2.0f * cursorxPos) / winWidth - 1;
	cursoryPos = 1.0f - (2.0f * cursoryPos) / winHeight;

	glm::vec2 cursorCoord(cursorxPos, cursoryPos);
	return cursorCoord;
}

void GUI::addButton(const Button& newButton) {
	_buttons.push_back(newButton);
}
void GUI::display() {
	for(Button& b : _buttons)
		b.draw();
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		GUI::_mouse_button_pressed = true;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		GUI::_mouse_button_pressed = false;
	}
}
void GUI::bindWindow(GLFWwindow* win) {
	window = win;

	glfwSetMouseButtonCallback(window, mouse_button_callback);
}

