
#ifndef CHARGE_H
#define CHARGE_H

#include <GL/glew.h>
#include <GL/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/vec2.hpp>

#include <vector>
#include <line.h>

class Charge {
public:
	Charge();
	Charge(GLfloat, glm::vec2);

	glm::vec2 getElectricField(glm::vec2 pos);
	glm::vec2 getPosition();

	GLfloat getCharge();

	std::vector<Line>& getFieldLines();
private:
	GLfloat Q;
	glm::vec2 position;

	std::vector<Line> fieldLines;
};

#endif