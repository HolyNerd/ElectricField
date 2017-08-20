#include <menu.h>

Menu::Menu() {
	_width = 0.05;
	_height = 0.05;
	_position = glm::vec2(0.0f, 0.0f);
	_menu_image.init();
	_menu_image.setShader("/home/holynerd/Desktop/Projects/ElectricField/Shaders/button");
	_is_visible = true;
}

Menu::Menu(const Menu& rhs) {
	_menu_image.init();
	_menu_image.setShader("/home/holynerd/Desktop/Projects/ElectricField/Shaders/button");

	_width = rhs._width;
	_height = rhs._height;
	_position = rhs._position;
	_image_path = rhs._image_path;

	_is_visible = true;

	_menu_name = rhs._menu_name;

	_menu_image.setPosition(_position);
	_menu_image.setRect(_position, _width, _height);
	_menu_image.setTexture(_image_path);
}

Menu::~Menu() {
	
}

void Menu::setPosition(glm::vec2 newPosition) {
	_menu_image.setPosition(newPosition);
	_position = newPosition;
}
void Menu::setSize(GLfloat width, GLfloat height) {
	_menu_image.setRect(_position, width, height);
	_width = width;
	_height = height;
}

void Menu::setImage(const char* imagePath) {
	_image_path = imagePath;
	_menu_image.setTexture(imagePath);
}

void Menu::setVisibility(bool visibility) {
	_is_visible = visibility;
}

void Menu::setName(const std::string& newName) { 
	_menu_name = newName;
}

const std::string Menu::getName() const {
	return _menu_name;
}

void Menu::draw() {
	if(_is_visible) {
		_menu_image.update();
		_menu_image.draw();
	}
}