
#include <charge.h>

Charge::Charge() { }
Charge::Charge(GLfloat charge, glm::vec2 pos) 
	: Q(charge), position(pos)
{ }

GLfloat Charge::getCharge() {
	return Q;
}

glm::vec2 Charge::getElectricField(glm::vec2 pos) {
	glm::vec2 unit = pos - position;
	GLfloat r = glm::length(unit);
	unit = glm::normalize(unit);

	GLfloat E = Q / pow(r, 2);

	glm::vec2 force = E * unit;

	return force;
}

glm::vec2 Charge::getPosition() {
	return position;
}