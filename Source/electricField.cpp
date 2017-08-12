
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
	
	Circle circle;
	circle.pos = pos;
	circle.radius = 0.01;
	chargeObjects.push_back(circle);
}

void ElectricField::createLines() {
	for(int c = 0; c < charges.size(); c++) {
		setLinesStartPoints(charges[c]);
		genField(charges[c]);
	}
}

void ElectricField::genField(Charge& charge) {
	for(int i = 0; i < charge.getFieldLines().size(); i++) {
		if(charge.getCharge() < 0) 
			genLine(charge.getFieldLines()[i], false);
		else
			genLine(charge.getFieldLines()[i], true);

		charge.getFieldLines()[i].updateBuffer();
		charge.getFieldLines()[i].setShader(lineShader);
	}
}

void ElectricField::genLine(Line& line, bool isPositive) {
	for(int p = 1; p > 0; p++) {
		glm::vec2 newPointPos;
		glm::vec2 prevPointPos;
		glm::vec2 netField;

		prevPointPos = line.getPoint(p-1);

		netField = getNetElectricField(prevPointPos);
		netField = glm::normalize(netField);

		if(!isPositive) 
			netField = netField * -1.0f;

		newPointPos = prevPointPos + netField * h;
		if(abs(newPointPos.x) >= 1 || abs(newPointPos.y) >= 1)
			return; 

		line.addPoint(newPointPos);

		for(Circle c : chargeObjects) 
			if(c.isInCircle(newPointPos)) 
				return;
	}
}


void ElectricField::drawLines() {
	glLineWidth(1.5f);

	for(Charge ch : charges)
		for(int i = 0; i < ch.getFieldLines().size(); i++)
			ch.getFieldLines()[i].draw();
}

glm::vec2 ElectricField::getNetElectricField(glm::vec2 pos) {
	glm::vec2 netField;

	for(int i = 0; i < charges.size(); i++) {
		glm::vec2 eField = charges[i].getElectricField(pos);
		netField += eField;
	}

	return netField;
}


void ElectricField::setLinesStartPoints(Charge& ch) {
	glm::vec2 pos = ch.getPosition();

	int n = 10 * abs(ch.getCharge());
	float a = 360.0 / n;
	a = glm::radians(a);

	glm::vec2 r(0.0f, 0.01f);
	glm::mat2 rotation (
		glm::vec2(cos(a),-sin(a)),
		glm::vec2(sin(a),cos(a))
	);

	for(int i = 0; i < n; i++) {
		ch.getFieldLines().push_back(Line(pos + r));
		r = r * rotation;
	}
}