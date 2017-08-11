
#include <electricField.h>
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/mat2x2.hpp>

ElectricField::ElectricField() { 
	h = 0.001f;
}

void ElectricField::init() {
	lineShader.shaderInfo("/home/holynerd/Desktop/Projects/ElectricField/Shaders/line");
}

void ElectricField::addCharge(GLfloat charge, glm::vec2 pos) {
	Charge c(charge, pos);
	charges.push_back(c);
}

void ElectricField::createLines() {
	fieldLines.clear();

	for(int c = 0; c < charges.size(); c++) {
		setLinesStartPoints(charges[c]);
	}

	for(int i = 0; i < fieldLines.size(); i++) {
		for(int p = 1; p < 60000; p++) {
			glm::vec2 newPointPos;
			glm::vec2 prevPointPos;
			glm::vec2 netField;

			prevPointPos = fieldLines[i].getPoint(p-1);

			netField = getNetElectricField(prevPointPos);
			netField = glm::normalize(netField);

			newPointPos = prevPointPos + netField * h;

			fieldLines[i].addPoint(newPointPos);
		}
		fieldLines[i].updateBuffer();
		fieldLines[i].setShader(lineShader);
	}
}
void ElectricField::drawLines() {
	glLineWidth(2.0f);
	for(int i = 0; i < fieldLines.size(); i++)
		fieldLines[i].draw();
}

glm::vec2 ElectricField::getNetElectricField(glm::vec2 pos) {
	glm::vec2 netField;

	for(int i = 0; i < charges.size(); i++) {
		glm::vec2 eField = charges[i].getElectricField(pos);
		netField += eField;
	}

	return netField;
}


void ElectricField::setLinesStartPoints(Charge ch) {
	if(ch.getCharge() < 0)
		return;

	glm::vec2 pos = ch.getPosition();
	GLfloat x = pos.x;
	GLfloat y = pos.y;

	int n = 8 * abs(ch.getCharge());
	float a = 360.0 / n;
	a = glm::radians(a);

	glm::vec2 r(0.0f, 0.01f);
	glm::mat2 rotation (
		glm::vec2(cos(a),-sin(a)),
		glm::vec2(sin(a),cos(a))
	);

	for(int i = 0; i < n; i++) {
		fieldLines.push_back(Line(pos + r));
		r = r * rotation;
	}
}