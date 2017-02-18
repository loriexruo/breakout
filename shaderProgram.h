#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	GLuint Program;
	// Constructor generates the shader on the fly
	// Uses the current shader
	void Generate(GLuint s);
	void Use() const;
	GLuint sUni(const char *s) const;//return uniform ID
	GLuint sUniB(const char *s) const;//return uniform block ID
	void SetMat4(const char *s, glm::mat4 p) const;
	void SetVec3(const char *s, glm::vec3 p) const;
	void SetInt(const char *s, GLint p) const;
	void Set1f(const char *s, GLfloat p) const;
};
#endif