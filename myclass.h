#ifndef MYCLASS_H
#define MYCLASS_H
#pragma once
#include <cmath>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class _mycircle {
public:
	glm::vec2 pos;
	glm::vec2 direc;
	GLfloat r;
	_mycircle(glm::vec2 position=glm::vec2(0), glm::vec2 direction=glm::vec2(0), GLfloat radius=0.0);
};

#endif