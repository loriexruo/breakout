#ifndef CIRCLE_H
#define CIRCLE_H
#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "soundPlayer.h"
#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "myfunc.h"
#include "particleManager.h"
#include "fruitsMng.h"
class Circle {
public:
	GLfloat radius, speed;
	glm::vec2 CircleCenterPos, runDirec;
	Texture2D tex;
	Circle();
	void InitCircle(glm::vec2 centerPos, glm::vec2 rundirec, GLfloat r, GLfloat v, Texture2D texture);
	void Run(GLfloat dt);
	void reflect(glm::vec2 normal, std::string obj);
	void Draw(SpriteRenderer &render);
	void Rotate(GLfloat angle);
	_mycircle GetInfo();
};
#endif