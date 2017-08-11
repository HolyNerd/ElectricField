
#ifndef LINE_H
#define LINE_H

#include <GL3/gl3w.h>
#include <GL/glfw3.h>

#include <glm/vec2.hpp>
#include <vector>
#include <shader.h>

class Line {
public:
	Line();
	Line(glm::vec2 startPoint);

	glm::vec2 getPoint(int i);
	int getSize();

	void addPoint(glm::vec2 point);

	void setShader(Shader);
	void updateBuffer();
	void draw();
private:
	std::vector<glm::vec2> controlPoints;

	Shader* shader;
	GLuint* buffers;
	GLuint vao;

	enum buffersIDs { positionBuffer, numBuffers };
};

#endif