#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader { 
public:
	Shader();
	Shader(const std::string shaderName);
	Shader(const Shader&);
	void shaderInfo(const std::string shaderName);

	operator GLuint();
private:
	GLuint program;

	GLuint createShader(GLenum type, const std::string);
	std::string readShader(const std::string);
};

#endif