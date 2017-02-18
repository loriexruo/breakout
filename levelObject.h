#ifndef LEVELOBJECT_H
#define LEVELOBJECT_H
#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <map>
#include "myfunc.h"
#include "spriteRenderer.h"
#include "brickObject.h"
class LevelObject {
private:
	std::vector<BrickObject*> bricks;
	GLuint lines, columns;
public:
	void load(GLuint levels, GLuint LinePix, GLuint ColumnPix);
	void Draw(SpriteRenderer &render);
	glm::vec2 Impact(_mycircle p);
	GLboolean allBricksCleared();
};
#endif
