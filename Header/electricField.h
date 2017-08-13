
#ifndef ELECTRIC_FIELD_H
#define ELECTRIC_FIELD_H

#include <charge.h>
#include <shader.h>
#include <line.h>

#include <vector>
#include <range.h>

#include <iostream>

#include <cmath>
#include <algorithm>

class ElectricField {
public:
	ElectricField();

	void init();

	void addCharge(GLfloat charge, glm::vec2 pos);
	void createLines();
	void drawLines();

	glm::vec2 getNetElectricField(glm::vec2 pos);
	GLfloat getNetPotential(glm::vec2 pos);

private:
	std::vector<Charge> charges;
	std::vector<Circle> chargeObjects;
	std::vector<Line> potential;

	GLfloat h;

	Shader lineShader;
	Shader potentialShader;
private:
	void setLinesStartPoints(Charge&);

	void genLine(Line&, bool isPositive);
	void genField(Charge&);

	void genPotential(Line line, GLfloat charge);
	void genPotential(glm::vec2 point);

	int getNextPoint(int i, float charge);

	glm::vec2 getPerpendicular(glm::vec2 v);
	bool isNear(glm::vec2 pos, glm::vec2 target, GLfloat radius);
	bool equal(const glm::vec2 &vecA, const glm::vec2 &vecB);
};

#endif