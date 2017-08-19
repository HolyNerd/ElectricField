
#include <iostream>
#include <application.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {

	Application app;
	app.init();

	while(!glfwWindowShouldClose(app.getWindow())) {

		//glfwSetFramebufferSizeCallback(app.getWindow(), framebuffer_size_callback);

		app.display();

		glfwSwapBuffers(app.getWindow());
		glfwPollEvents();
	}

	app.shutdown();

	return 0;
}
