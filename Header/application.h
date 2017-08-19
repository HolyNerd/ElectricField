
#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>

#include <GL/glew.h>
#include <GL/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>
#include <glm/ext.hpp>

#include <sprite.h>
#include <shader.h>
#include <electricField.h>
#include <GUI.h>

class Application {
public:
	Application(GLFWwindow*);
	~Application();

	void init();
	void display();
	void shutdown();
private:
	ElectricField electricField;
public: GLFWwindow* getWindow() const;
private: 
	Button button;
	Button* button2;

	GLFWwindow* window;
	GUI gui;

	Sprite background;
};

#endif