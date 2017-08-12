
#include <line.h>
#include <GL3/gl3w.h>
#include <GL/glfw3.h>
#include <iostream>
Line::Line() { 
	buffers = new GLuint[numBuffers];
	shader = new Shader();
}
Line::Line(glm::vec2 startPoint) { 
	controlPoints.push_back(startPoint); 

	buffers = new GLuint[numBuffers];
	shader = new Shader();
}

void Line::addPoint(glm::vec2 point) {
	controlPoints.push_back(point);
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

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Line::draw() {
	glUseProgram(*shader);
	glBindVertexArray(vao);
	glDrawArrays(GL_LINE_STRIP, 0, controlPoints.size());
	glBindVertexArray(0);
}
