
#include <electricField.h>

#include <iostream>
#include <math.h>

#include <glm/vec3.hpp>
#include <glm/mat2x2.hpp>
#include <glm/glm.hpp>

ElectricField::ElectricField() {
	h = 0.001f;
}

void ElectricField::init() {
	lineShader.shaderInfo("/home/holynerd/Desktop/Projects/ElectricField/Shaders/line");
	potentialShader.shaderInfo("/home/holynerd/Desktop/Projects/ElectricField/Shaders/potential");
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
	potential.clear();
	for(int i = 0; i < charges.size(); i++) {
		charges[i].getFieldLines().clear();
	}

	for(int c = 0; c < charges.size(); c++) {
		setLinesStartPoints(charges[c]);
		genField(charges[c]);	

		std::vector<Line>& chargeLines = charges[c].getFieldLines();
		std::sort(chargeLines.begin(), chargeLines.end());
		genPotential(chargeLines[chargeLines.size()-1], charges[c].getCharge());
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

void ElectricField::genPotential(Line line, GLfloat charge) {
	bool drawThisLine = false;

	int prevIndex = 0;
	int i = 1;

	while(i < line.getSize()) {
		int nextIndex = getNextPoint(i, charge);

		float nextLineMagnitude = getNetPotential(line.getPoint(nextIndex));
		if(nextIndex > line.getSize())
			nextLineMagnitude = getNetPotential(line.getPoint(i)) + 10;
		float prevLineMagnitude = getNetPotential(line.getPoint(prevIndex));

		float currMagnitude = getNetPotential(line.getPoint(i));

		if(std::signbit(nextLineMagnitude) != std::signbit(currMagnitude))
			return;

		Range magnitudeRange;
		magnitudeRange.start = nextLineMagnitude;
		magnitudeRange.end = prevLineMagnitude;

		drawThisLine = true;

		for(int p = 0; p < potential.size(); p++) {
			bool b = magnitudeRange.isIn(getNetPotential(potential[p].getPoint(0)));
			if(b) {
				if(line.isIntersects(prevIndex, nextIndex, potential[p])) {
					drawThisLine = false;
					return;
				}
			}
		}

		prevIndex = i;
		if(drawThisLine) {
			genPotential(line.getPoint(i));
		}
		i = getNextPoint(i, charge);
	}
}

void ElectricField::genPotential(glm::vec2 point) {
	float f = 0.001;

	Line line;
	line.addPoint(point);

	glm::vec2 newPointPos;
	glm::vec2 prevPointPos;
	glm::vec2 netField;
			
	glm::vec2 potentialDir;

	GLfloat netPotential = getNetPotential(point);

	for(int i = 1; i < 33000; i++) {
		prevPointPos = line.getPoint(i-1);

		netField = getNetElectricField(prevPointPos);
		netField = glm::normalize(netField);

		potentialDir = getPerpendicular(netField);

		netField = getNetElectricField(prevPointPos + potentialDir * f);
		netField = glm::normalize(netField);

		glm::vec2 slope = getPerpendicular(netField);

		slope = (potentialDir + slope) / 2;

		newPointPos = prevPointPos + slope * f;

		line.addPoint(newPointPos);

		if(i > 100 && isNear(point, newPointPos, f)) {
			line.addPoint(point);
			break;
		}
	}
	line.setShader(potentialShader);

	line.setColor(glm::vec4(150.0/255, 150.0/255, 150.0/255, 0.90 * abs(netPotential)/1000));
	line.updateBuffer();
	
	potential.push_back(Line(line));
}

int ElectricField::getNextPoint(int i, float charge) {
	float f = i;

	int c = i;
	while(c == i) {
		f += f / abs(charge);
		i = f;
	}
	return i;
}

void ElectricField::genLine(Line& line, bool isPositive) {
	for(int p = 1; p < 60000; p++) {
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

		glm::vec2 nextNetField = getNetElectricField(newPointPos);
		nextNetField = glm::normalize(nextNetField);
		
		if(isPositive)
			nextNetField*=-1;

		if(equal(nextNetField, netField)) {
			line.clear();
			return;
		}
		for(Circle c : chargeObjects) 
			if(c.isInCircle(newPointPos)) 
				return;
	}
}

void ElectricField::drawLines() {
	glLineWidth(1);
	for(int i = 0; i < potential.size(); i++)
		potential[i].draw();
	
	glLineWidth(1.0f);

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

GLfloat ElectricField::getNetPotential(glm::vec2 pos) {
	GLfloat sum = 0;
	for(int i = 0; i < charges.size(); i++) {
		glm::vec2 dist = pos - charges[i].getPosition();
		GLfloat r = glm::length(dist);
		GLfloat potential = charges[i].getCharge() / r * 100;
		sum += potential; 
	}
	return sum;
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

bool ElectricField::isNear(glm::vec2 pos, glm::vec2 target, GLfloat radius) {
	Circle c;
	c.pos = pos;
	c.radius = radius;
	if(c.isInCircle(target))
		return true;
	return false;
}

bool ElectricField::equal(const glm::vec2 &vecA, const glm::vec2 &vecB) {
	const double epsilion = 0.0001;
	return fabs(vecA[0] -vecB[0]) < epsilion   
 		&& fabs(vecA[1] -vecB[1]) < epsilion;
}

glm::vec2 ElectricField::getPerpendicular(glm::vec2 v) {
	glm::vec2 perp(-v.y, v.x);
		return perp;
}

