
#ifndef RANGE_H
#define RANGE_H

#include <glm/vec2.hpp>

struct Range {
	int start;
	int end;

	bool isIn(int i) {
		if(i >= start && i <= end)
			return true;
		return false;
	}
};

struct Circle {
	glm::vec2 pos;
	float radius;
	bool isInCircle(glm::vec2 p) {
		glm::vec2 r = p - pos;
		if(glm::length(r) > radius)
			return false;
		return true;
	}
};

#endif