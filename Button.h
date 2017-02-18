#pragma once
#ifndef BUTTON_H
#define BUTTON_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "soundPlayer.h"
#include "spriteRenderer.h"
#include "myfunc.h"
class Button {
private:
	glm::vec2 position, size;
public:
	Button(glm::vec2 pos = glm::vec2(0, 0), glm::vec2 siz = glm::vec2(100, 20));
	GLboolean IfClick(glm::vec2 pressPos, glm::vec2 releasePos);
	void Draw(SpriteRenderer &render, Texture2D tex);
};
#endif