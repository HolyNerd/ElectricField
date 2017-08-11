
#ifndef CHARGE_H
#define CHARGE_H

#include <GL3/gl3w.h>
#include <GL/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/vec2.hpp>

class Charge {
public:
	Charge();
	Charge(GLfloat, glm::vec2);

	glm::vec2 getElectricField(glm::vec2 pos);
	glm::vec2 getPosition();

	GLfloat getCharge();
private:
	GLfloat Q;
	glm::vec2 position;
};

#endif