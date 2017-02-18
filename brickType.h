#ifndef BRICKTYPE_H
#define BRICKTYPE_H
#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "spriteRenderer.h"
//save all info of a level.
class brickType {
public:
	GLboolean isColor;
	glm::vec3 color;
	Texture2D tex;
	brickType() {}
	brickType(GLboolean iscolor, glm::vec3 col);
	brickType(GLboolean iscolor, Texture2D texture);
};
#endif