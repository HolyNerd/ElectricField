#ifndef MENU_H
#define MENU_H

#include <string>
#include <GL/glew.h>
#include <glm/vec2.hpp>

#include <range.h>
#include <sprite.h>

#include <GL/glfw3.h>

class Menu {
public:
	Menu();
	Menu(const Menu&);
	~Menu();

	void setPosition(glm::vec2);
	void setSize(GLfloat width, GLfloat height);
	void setImage(const char* imagePath);
	void setName(const std::string& name);
	void setVisibility(bool visibility);

	const std::string getName() const;

	void draw();

private:
	Sprite _menu_image;

	GLfloat _width;
	GLfloat _height;
	glm::vec2 _position;

	const char* _image_path;

	std::string _menu_name;

	bool _is_visible;
};

#endif