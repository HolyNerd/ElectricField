

#include <GL/glew.h>
#include <GL/glfw3.h>

#include <iostream>
#include <application.h>

int main() {
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(900, 900, "OpenGL: Electric Field", NULL, NULL);
	glfwMakeContextCurrent(window);

	glewInit();

	Application app(window);
	app.init();

	while(!glfwWindowShouldClose(window)) {
		app.display();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	app.shutdown();

	return 0;
}
