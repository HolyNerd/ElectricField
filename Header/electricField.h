
#ifndef ELECTRIC_FIELD_H
#define ELECTRIC_FIELD_H

#include <charge.h>
#include <shader.h>
#include <line.h>

#include <vector>
#include <range.h>

class ElectricField {
public:
	ElectricField();

	void init();

	void addCharge(GLfloat charge, glm::vec2 pos);
	void createLines();
	void createEquipotential();

	void drawLines();

	glm::vec2 getNetElectricField(glm::vec2 pos);
private:
	std::vector<Charge> charges;
	std::vector<Line> fieldLines;
	GLfloat h;

	Shader lineShader;
private:
	void setLinesStartPoints(Charge);
};



#endif