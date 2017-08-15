
#include <iostream>
#include <application.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
	std::cout << "1" << std::endl;
	Application app;
	std::cout << "1" << std::endl;
	app.init();
	std::cout << "1" << std::endl;
	while(!glfwWindowShouldClose(app.getWindow())) {

		glfwSetFramebufferSizeCallback(app.getWindow(), framebuffer_size_callback);

		app.display();

		glfwSwapBuffers(app.getWindow());
		glfwPollEvents();
	}

	app.shutdown();

	return 0;
}
