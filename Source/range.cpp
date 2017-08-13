#include <range.h>

bool Range::isIn(int i) {
	if(i < end && i > start) { 
		return true;
	}
	else {
		return false;
	}
}

bool Circle::isInCircle(glm::vec2 p) {
	glm::vec2 r = p - pos;
	if(glm::length(r) > radius)
		return false;
	return true;
}