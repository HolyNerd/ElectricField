#ifndef GUI_H
#define GUI_H

#include <vector>
#include <string>

#include <GL/glew.h>
#include <GL/glfw3.h>

#include <glm/vec2.hpp>

#include <menu.h>
#include <button.h>

class GUI {
public:
	GUI();
	~GUI();

	const glm::vec2 getMousePosition();

	bool isButtonPressed(std::string buttonName);

	void addElement(const Button& newButton);
	void addElement(const Menu& newMenu);

	void setVisibility(const std::string name, bool);

	void display();

	void bindWindow(GLFWwindow*);

	static bool _mouse_button_pressed;
	static bool _mouse_button_released;
	static bool _mouse_right_button_pressed;
private:
	std::vector<Button> _buttons;
	std::vector<Menu> _menus;
	GLFWwindow* window;
};

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

#endif