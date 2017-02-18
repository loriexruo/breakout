#pragma once
#ifndef MOUSE_H
#define MOUSE_H
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "myfunc.h"
#include "spriteRenderer.h"
#include "Texture2D.h"
#include "particleManager.h"

class Mouse {
	Texture2D tex;
	glm::vec2 mouseSize;
	glm::vec2 windowSize;
	glm::vec2 wndwpos, lastPos;
	GLboolean setFirst;
	glm::vec2 pushPos, freePos;
	GLboolean pushed;
	void press();
	void release();
public:
	Mouse(glm::vec2 wndwSize, glm::vec2 mousePos, Texture2D Tex, glm::vec2 msSize = glm::vec2(16,20));
	void Move(glm::vec2 newmousePos);
	void mouseButton(int button, int action);
	std::pair<glm::vec2, glm::vec2> GetClick();
	void Draw(SpriteRenderer &render);
};
#endif