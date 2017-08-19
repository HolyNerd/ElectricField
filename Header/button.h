#ifndef BUTTON_H
#define BUTTON_H

#include <string>

#include <GL/glew.h>
#include <glm/vec2.hpp>

#include <range.h>
#include <sprite.h>

class Button {
public:
	Button();
	Button(const Button&);
	~Button();

	const std::string& getName() const;

	void setPosition(glm::vec2);
	void setSize(GLfloat width, GLfloat height);
	void setButtonImage(const char* filePath);
	void setButtonName(const std::string&);

	bool isIn(glm::vec2 point);

	void draw();
private:
	Sprite _button_image;

	GLfloat _width;
	GLfloat _height;
	glm::vec2 _position;

	const char* _image_path;

	std::string _button_name;
};

#endif