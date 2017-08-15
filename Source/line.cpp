
#include <line.h>
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <range.h>

Line::Line() { 
	buffers = new GLuint[numBuffers];
	shader = new Shader();
	lineColor = glm::vec4((121)/255.0f, (154)/255.0f, (209)/255.0f, 1.0);
}
Line::Line(glm::vec2 startPoint) { 
	controlPoints.push_back(startPoint); 

	buffers = new GLuint[numBuffers];
	shader = new Shader();
	lineColor = glm::vec4((121)/255.0f, (154)/255.0f, (209)/255.0f, 1.0);
}

Line::Line(const Line& rhs) { 

	controlPoints = rhs.controlPoints;

	buffers = new GLuint[numBuffers];
	shader = new Shader();
	*shader = *(rhs.shader);

	lineColor = rhs.lineColor;

	glCreateBuffers(numBuffers, buffers);
	glCreateVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[positionBuffer]);

	glBufferData(
		GL_ARRAY_BUFFER, 
		controlPoints.size() * sizeof(glm::vec2), 
		controlPoints.data(), 
		GL_STATIC_DRAW
	);


	glVertexArrayVertexBuffer(vao, 0, buffers[positionBuffer], 0, 
		sizeof(GLfloat)*2);
	glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);

	glVertexAttribBinding(0, 0);
	glEnableVertexAttribArray(0);


	GLfloat color[4];
	color[0] = lineColor.r;
	color[1] = lineColor.g;
	color[2] = lineColor.b;
	color[3] = lineColor.a;
	glBindBuffer(GL_ARRAY_BUFFER, buffers[colorBuffer]);

	glBufferData(
		GL_ARRAY_BUFFER, 
		sizeof(color), 
		color, 
		GL_STATIC_DRAW
	);


	glVertexArrayVertexBuffer(vao, 1, buffers[colorBuffer], 0, 0);
	glVertexArrayAttribFormat(vao, 1, 4, GL_FLOAT, GL_FALSE, 0);

	glVertexAttribBinding(1, 1);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Line::addPoint(glm::vec2 point) {
	controlPoints.push_back(point);
}

void Line::clear() {
	glm::vec2 startPoint = controlPoints[0];
	controlPoints.clear();
	controlPoints.push_back(startPoint);
}

bool Line::isIntersects(int startPoint, int endPoint, Line& rhs) {

	for(int i = startPoint; i < endPoint; i++) {

		glm::vec2 currPoint = controlPoints[i];


		for(int p = 0; p < rhs.getSize(); p++) {
			if(isNear(currPoint, rhs.getPoint(p), 0.001)) {

				return true;
			}

		}
	}
	return false;
}

void Line::setShader(Shader shader) {
	this->shader = new Shader(shader);
}

glm::vec2 Line::getPoint(int i) {
	return controlPoints[i];
}

int Line::getSize() {
	return controlPoints.size();
}

void Line::updateBuffer() {
	for(int i = 0; i < numBuffers; i++) 
		if(glIsBuffer(buffers[i]) == GL_FALSE) 
			glCreateBuffers(1, &buffers[i]); 
		
	if(glIsVertexArray(vao) == GL_FALSE) 
		glCreateVertexArrays(1, &vao); 


	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[positionBuffer]);

	glBufferData(
		GL_ARRAY_BUFFER, 
		controlPoints.size() * sizeof(glm::vec2), 
		controlPoints.data(), 
		GL_STATIC_DRAW
	);


	glVertexArrayVertexBuffer(vao, 0, buffers[positionBuffer], 0, 
		sizeof(GLfloat)*2);
	glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);

	glVertexAttribBinding(0, 0);
	glEnableVertexAttribArray(0);



	GLfloat color[4];
	color[0] = lineColor.r;
	color[1] = lineColor.g;
	color[2] = lineColor.b;
	color[3] = lineColor.a;
	glBindBuffer(GL_ARRAY_BUFFER, buffers[colorBuffer]);

	glBufferData(
		GL_ARRAY_BUFFER, 
		sizeof(color), 
		color, 
		GL_STATIC_DRAW
	);


	glVertexArrayVertexBuffer(vao, 1, buffers[colorBuffer], 0, 0);
	glVertexArrayAttribFormat(vao, 1, 4, GL_FLOAT, GL_FALSE, 0);

	glVertexAttribBinding(1, 1);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Line::setColor(glm::vec4 newColor) {
	lineColor = newColor;
}

void Line::draw() {
	glBindVertexArray(vao);
	glUseProgram(*shader);
	
	glDrawArrays(GL_LINE_STRIP, 0, controlPoints.size());
	glBindVertexArray(0);
}


bool Line::isNear(glm::vec2 pos, glm::vec2 target, GLfloat radius) {
	Circle c;
	c.pos = pos;
	c.radius = radius;
	if(c.isInCircle(target))
		return true;
	return false;
}

bool Line::equal(const glm::vec2 &vecA, const glm::vec2 &vecB) {
	const double epsilion = 0.0001;
	return fabs(vecA[0] -vecB[0]) < epsilion   
 		&& fabs(vecA[1] -vecB[1]) < epsilion;
}


bool Line::operator==(const Line& rhs) {
	glm::vec2 lhsLength = controlPoints[controlPoints.size()-1]-controlPoints[0];
	glm::vec2 rhsLength = rhs.controlPoints[rhs.controlPoints.size()-1]-rhs.controlPoints[0];

	if(glm::length(lhsLength) == glm::length(rhsLength))
		return true;
	return false;
}
bool Line::operator!=(const Line& rhs) {
	glm::vec2 lhsLength = controlPoints[controlPoints.size()-1]-controlPoints[0];
	glm::vec2 rhsLength = rhs.controlPoints[rhs.controlPoints.size()-1]-rhs.controlPoints[0];

	if(glm::length(lhsLength) != glm::length(rhsLength))
		return true;
	return false;
}
bool Line::operator>(const Line& rhs) {
	glm::vec2 lhsLength = controlPoints[controlPoints.size()-1]-controlPoints[0];
	glm::vec2 rhsLength = rhs.controlPoints[rhs.controlPoints.size()-1]-rhs.controlPoints[0];

	if(glm::length(lhsLength) > glm::length(rhsLength))
		return true;
	return false;
}
bool Line::operator<(const Line& rhs) {
	glm::vec2 lhsLength = controlPoints[controlPoints.size()-1]-controlPoints[0];
	glm::vec2 rhsLength = rhs.controlPoints[rhs.controlPoints.size()-1]-rhs.controlPoints[0];

	if(glm::length(lhsLength) < glm::length(rhsLength))
		return true;
	return false;
}
bool Line::operator>=(const Line& rhs) {
	glm::vec2 lhsLength = controlPoints[controlPoints.size()-1]-controlPoints[0];
	glm::vec2 rhsLength = rhs.controlPoints[rhs.controlPoints.size()-1]-rhs.controlPoints[0];

	if(glm::length(lhsLength) >= glm::length(rhsLength))
		return true;
	return false;
}
bool Line::operator<=(const Line& rhs) {
	glm::vec2 lhsLength = controlPoints[controlPoints.size()-1]-controlPoints[0];
	glm::vec2 rhsLength = rhs.controlPoints[rhs.controlPoints.size()-1]-rhs.controlPoints[0];

	if(glm::length(lhsLength) <= glm::length(rhsLength))
		return true;
	return false;
}