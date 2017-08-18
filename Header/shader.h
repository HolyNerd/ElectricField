#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader { 
public:
	// Constructors
	Shader();
	Shader(const std::string shaderName);
	Shader(const Shader&);
	
	// Set shader source
	void shaderInfo(const std::string shaderName);

	// Convert Shader object to program, needed by "glUseProgram(GLuint)"
	operator GLuint();
private:
	GLuint program;

	GLuint createShader(GLenum type, const std::string);
	std::string readShader(const std::string);
};

#endif