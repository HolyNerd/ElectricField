
#include <GUI.h>
#include <iostream>

GUI::GUI() {

}

GUI::~GUI() {

}

bool GUI::isButtonPressed(std::string buttonName) {
	if(glfwGetTime() < 0.3)
		return false;

	glm::vec2 mousePosition = getMousePosition();

	for(Button& button : _buttons) {
		if(button.getName() == buttonName && button.isIn(mousePosition)) {
			if(_mouse_button_pressed == true) {
				glfwSetTime(0.0f);
				button.setPress(true);
				return true;
			}
			else if (_mouse_button_released == true)  {
				button.setPress(false);
				return false;
			}
		}
	}		
}

bool GUI::_mouse_button_pressed = false;
bool GUI::_mouse_button_released = false;
bool GUI::_mouse_right_button_pressed = false;

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

void GUI::addElement(const Button& newButton) {
	_buttons.push_back(newButton);
}
void GUI::addElement(const Menu& newMenu) {
	_menus.push_back(newMenu);
}

void GUI::setVisibility(const std::string name, bool visibility) {
	for(Menu& m : _menus) 
		if(m.getName() == name) {
			m.setVisibility(visibility);
			return;
		}
}

void GUI::display() {
	for(Button& b : _buttons)
		b.draw();
	for(Menu& m: _menus) 
		m.draw();
}

void GUI::bindWindow(GLFWwindow* win) {
	window = win;

	glfwSetMouseButtonCallback(window, mouse_button_callback);
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		GUI::_mouse_button_pressed = true;
		GUI::_mouse_button_released = false;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		GUI::_mouse_button_pressed = false;
		GUI::_mouse_button_released = true;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		GUI::_mouse_right_button_pressed = true;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
		GUI::_mouse_right_button_pressed = false;
	}
}

