#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <map>

#include "spriteRenderer.h"
#include "Button.h"
#include "Texture2D.h"
class Interface {
private:
	std::map<std::string, std::pair<Texture2D, Button>> buttons;
	Texture2D back;
	glm::vec2 faceSize;
public:
	Interface(glm::vec2 Size, Texture2D background);
	void AddButton(glm::vec2 pos, glm::vec2 size, Texture2D tex, std::string name);
	std::string GetClick(std::pair<glm::vec2, glm::vec2> sp);
	void Draw(SpriteRenderer &render);
};
#endif