
#ifndef LINE_H
#define LINE_H

#include <GL3/gl3w.h>
#include <GL/glfw3.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/glm.hpp>

#include <vector>
#include <shader.h>

#include <iostream>

class Line {
public:
	Line();
	Line(glm::vec2 startPoint);
	Line(const Line&);

	glm::vec2 getPoint(int i);
	int getSize();

	void addPoint(glm::vec2 point);

	bool isIntersects(int startPoint, int endPoint, Line& rhs);

	void clear();
	void setShader(Shader);
	void updateBuffer();
	void draw();

	void setColor(glm::vec4 newColor);

	bool operator==(const Line& rhs);
	bool operator!=(const Line& rhs);
	bool operator>(const Line& rhs);
	bool operator<(const Line& rhs);
	bool operator>=(const Line& rhs);
	bool operator<=(const Line& rhs);
	
private:
	bool equal(const glm::vec2 &vecA, const glm::vec2 &vecB);
	bool isNear(glm::vec2 pos, glm::vec2 target, GLfloat radius);

	std::vector<glm::vec2> controlPoints;

	glm::vec4 lineColor;

	Shader* shader;
	GLuint* buffers;
	GLuint vao;

	enum buffersIDs { positionBuffer, colorBuffer, numBuffers };
};

#endif