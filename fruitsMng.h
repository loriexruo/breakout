#pragma once
#ifndef FRUITSMNG_H
#define FRUITSMNG_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>

#include "resourceManager.h"
#include "myfunc.h"
#include "Texture2D.h"
#include "spriteRenderer.h"
#include "fruit.h"
#include "paddle.h"

class FruitsManager {
private:
	static std::map<std::string, float> bufftime;
	static std::map<GLuint, Fruit*> fruits;
	static GLuint fruitsNum;
	static glm::vec2 wndwSize;
	FruitsManager() {}
public:
	static void Init(glm::vec2 size);
	static GLboolean haveBuff(std::string);
	static void Updata(GLfloat dt, std::pair<glm::vec2, glm::vec2> line, glm::vec2 normal);
	static void AddFruit(glm::vec2 pos, glm::vec2 rundirec, GLfloat r, GLfloat time, std::string bufftype);
	static void Draw(SpriteRenderer &render);
	static void Clear();
};
#endif