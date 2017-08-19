#ifndef GUI_H
#define GUI_H

#include <vector>
#include <string>

#include <GL/glew.h>
#include <GL/glfw3.h>

#include <glm/vec2.hpp>

#include <button.h>

class GUI {
public:
	GUI();
	~GUI();

	const glm::vec2 getMousePosition();

	bool isButtonPressed(std::string buttonName);

	void addButton(const Button& newButton);
	void display();

	void bindWindow(GLFWwindow*);

	static bool _mouse_button_pressed;

private:
	std::vector<Button> _buttons;
	GLFWwindow* window;
};

#endif