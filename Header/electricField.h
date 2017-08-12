
#ifndef ELECTRIC_FIELD_H
#define ELECTRIC_FIELD_H

#include <charge.h>
#include <shader.h>
#include <line.h>

#include <vector>
#include <range.h>

#include <iostream>

#include <cmath>

class ElectricField {
public:
	ElectricField();

	void init();

	void addCharge(GLfloat charge, glm::vec2 pos);
	void createLines();
	void drawLines();

	glm::vec2 getNetElectricField(glm::vec2 pos);
private:
	std::vector<Charge> charges;
	std::vector<Circle> chargeObjects;

	GLfloat h;

	Shader lineShader;
private:
	void setLinesStartPoints(Charge&);

	void genLine(Line&, bool isPositive);
	void genField(Charge&);
};

#endif