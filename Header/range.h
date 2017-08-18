
#ifndef RANGE_H
#define RANGE_H

#include <glm/vec2.hpp>
#include <glm/glm.hpp>

struct Range {
	int start;
	int end;

	bool isIn(int i);
};

struct Circle {
	glm::vec2 pos;
	float radius;
	
	bool isInCircle(glm::vec2 p);
};

#endif