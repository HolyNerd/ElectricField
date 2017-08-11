
#include <iostream>
#include <application.h>

int main() {
	Application app;

	app.init();
	
	while(!glfwWindowShouldClose(app.getWindow())) {
		app.display();

		glfwSwapBuffers(app.getWindow());
		glfwPollEvents();
	}

	app.shutdown();

	return 0;
}
