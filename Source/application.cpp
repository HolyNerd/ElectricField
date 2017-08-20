
#include <application.h>

#include <chrono>
#include <iostream>

#include <line.h>
#include <button.h>


#define HIGH_QUALITY

Application::Application(GLFWwindow* win) 
	: window(win)
{

	mode = DISPLAY;

	isUpdated = false;

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
	GLfloat buttonWidth = 0.22;
	GLfloat buttonHeight = 0.074;

	Menu menu;
	menu.setPosition(glm::vec2(-0.5, -0.5));
	menu.setSize(1, 1);
	menu.setImage("/home/holynerd/Desktop/Projects/ElectricField/Media/GUI/menu.png");
	menu.setName("Menu1");
	gui.addElement(menu);

	gui.setVisibility("Menu1", false);

	Button button;
	button.setPosition(glm::vec2(-0.86, 0.9));
	button.setSize(buttonWidth * 1.5, buttonHeight * 1.5);
	button.setUnpressedButtonImage("/home/holynerd/Desktop/Projects/ElectricField/Media/GUI/button_add.png");
	button.setPressedButtonImage("/home/holynerd/Desktop/Projects/ElectricField/Media/GUI/pressed_button_add.png");
	button.setButtonName("Button1");
	gui.addElement(button);

	button.setPosition(glm::vec2(-0.86, 0.8));
	button.setUnpressedButtonImage("/home/holynerd/Desktop/Projects/ElectricField/Media/GUI/button_move.png");
	button.setPressedButtonImage("/home/holynerd/Desktop/Projects/ElectricField/Media/GUI/pressed_button_move.png");
	button.setButtonName("Button2");
	gui.addElement(button);

	button.setPosition(glm::vec2(-0.86, 0.7));
	button.setUnpressedButtonImage("/home/holynerd/Desktop/Projects/ElectricField/Media/GUI/button_delete.png");
	button.setPressedButtonImage("/home/holynerd/Desktop/Projects/ElectricField/Media/GUI/pressed_button_delete.png");
	button.setButtonName("Button3");
	gui.addElement(button);

	button.setPosition(glm::vec2(-0.86, 0.6));
	button.setUnpressedButtonImage("/home/holynerd/Desktop/Projects/ElectricField/Media/GUI/button.png");
	button.setPressedButtonImage("/home/holynerd/Desktop/Projects/ElectricField/Media/GUI/button.png");
	button.setButtonName("Button4");
	gui.addElement(button);

	electricField.init();

	gui.bindWindow(window);
}

void Application::display() {
	if(gui.isButtonPressed("Button1")) {
		mode = EDIT_ADD;
		isUpdated = true;
		return;
	}
	if(gui.isButtonPressed("Button2")) {
		mode = EDIT_MOVE;
		isUpdated = true;
		return;
	}
	if(gui.isButtonPressed("Button3")) {
		editMode_delete();
	}
	if(gui.isButtonPressed("Button4")) {
		static bool isVisible = true;
		gui.setVisibility("Menu1", !isVisible);
		isVisible = !isVisible;
	}

	if(isUpdated) {
		electricField.clear();
		for(Charge& ch : charges)
			electricField.addCharge(ch.getCharge(), ch.getPosition());
		electricField.createLines(true, true);
		isUpdated = false;
	}

	background.draw();
	electricField.drawLines(true);
	gui.display();
}

void Application::editMode_add() {
		if(gui.isButtonPressed("Button1")) {
			mode = DISPLAY;
			
			background.draw();
			electricField.drawSprites();	
			gui.display();
			
			return;
		}
		if(GUI::_mouse_right_button_pressed) {
			mode = DISPLAY;

			background.draw();
			electricField.drawSprites();	
			gui.display();

			return;
		}

		electricField.clear();

		for(Charge& ch : charges)
			electricField.addCharge(ch.getCharge(), ch.getPosition());

		Charge ch(1, gui.getMousePosition());
		electricField.addCharge(ch.getCharge(), ch.getPosition());

		if(GUI::_mouse_button_pressed && glfwGetTime() > 0.3) {
			mode = DISPLAY;
			charges.push_back(ch);
			return;
		}

		background.draw();
		electricField.drawSprites();	
		gui.display();
}

Charge* Application::getCharge(glm::vec2 pos) {
	for(int i = 0; i < charges.size(); i++) {
		Circle border { charges[i].getPosition(), 0.05 };

		if(border.isInCircle(pos))
			return &charges[i];
	}
	return nullptr;
}

void Application::editMode_move() {
	if(gui.isButtonPressed("Button1")) 
		editMode_add();
	if(gui.isButtonPressed("Button2")) {
		mode = DISPLAY;
		
		background.draw();
		electricField.drawSprites();	
		gui.display();
		
		return;
	}
	if(gui.isButtonPressed("Button4")) {
		
	}

	static bool isFinding = true;
	static glm::vec2 startPosition;
	static Charge* charge;

	if(GUI::_mouse_button_pressed && glfwGetTime() > 0.3 && isFinding) {
		glm::vec2 mousePos = gui.getMousePosition();

		charge = getCharge(mousePos);

		if(charge == nullptr) {
			mode = DISPLAY;
			return;
		}
		else {
			isFinding = false;
			startPosition = charge->getPosition();
			glfwSetTime(0.0);
		}
	}

	if(!isFinding) {
		charge->setPosition(gui.getMousePosition());
		electricField.clear();

		for(Charge& ch : charges)
			electricField.addCharge(ch.getCharge(), ch.getPosition());

		if(GUI::_mouse_button_pressed && glfwGetTime() > 0.3) {
			mode = DISPLAY;
			isFinding = true;
			return;
		}
		if(GUI::_mouse_right_button_pressed) {
			mode = DISPLAY;
	
			background.draw();
			electricField.drawSprites();	
			gui.display();
	
			charge->setPosition(startPosition);
	
			return;
		}
	}
	

	background.draw();
	electricField.drawSprites();	
	gui.display();
}
void Application::editMode_delete() {
	if(gui.isButtonPressed("Button1")) 
		editMode_add();
	if(gui.isButtonPressed("Button2")) {
	
		editMode_move();
	}
	if(gui.isButtonPressed("Button3")) 
		return;
	if(gui.isButtonPressed("Button4")) {
			
		}

	std::cout << "3\n";
	
}


void Application::shutdown() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

GLFWwindow* Application::getWindow() const { 
	return window;
}

Application::Mode Application::getMode() {
	return mode;
}