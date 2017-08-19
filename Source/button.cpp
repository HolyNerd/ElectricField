
#include <button.h>
#include <iostream>

Button::Button() {
	_width = 0.05;
	_height = 0.05;
	_position = glm::vec2(0.0f, 0.0f);
	_button_image.init();
	_button_image.setShader("/home/holynerd/Desktop/Projects/ElectricField/Shaders/button");
}
Button::Button(const Button& rhs){ 
	_button_image.init();
	_button_image.setShader("/home/holynerd/Desktop/Projects/ElectricField/Shaders/button");

	_width = rhs._width;
	_height = rhs._height;
	_position = rhs._position;
	_image_path = rhs._image_path;
	_button_name = rhs._button_name;

	_button_image.setPosition(_position);
	_button_image.setRect(_position, _width, _height);
	_button_image.setTexture(_image_path);
}
Button::~Button() {

}


bool Button::isIn(glm::vec2 point) {
	glm::vec2 top_left;
	glm::vec2 down_right;

	top_left.x = _position.x - _width/2;
	down_right.x = _position.x + _width/2;
	top_left.y = _position.y + _height/2;
	down_right.y = _position.y - _height/2;

	Area area { top_left, down_right };
	
	if(area.isInArea(point)) 
		return true;

	return false;
}

const std::string& Button::getName() const {
	return _button_name;
}

void Button::setPosition(glm::vec2 newPosition) {
	_button_image.setPosition(newPosition);
	_position = newPosition;
}
void Button::setSize(GLfloat width, GLfloat height) {
	_button_image.setRect(_position, width, height);
	_width = width;
	_height = height;
}
void Button::setButtonImage(const char* filePath) {
	_image_path = filePath;
	_button_image.setTexture(filePath);
}

void Button::setButtonName(const std::string& name) {
	_button_name = name;
}

void Button::draw() {
	_button_image.update();
	_button_image.draw();
}