#pragma once
#ifndef FRUIT_H
#define FRUIT_H
#include "myfunc.h"
#include "Texture2D.h"
#include "spriteRenderer.h"

class Fruit {
	_mycircle info;
	Texture2D tex;
	std::string buff;
	GLfloat bufftime;
	GLboolean exist;
public:
	Fruit(_mycircle inf, Texture2D Tex, std::string buf, GLfloat tm);
	_mycircle GetInfo();
	std::pair<std::string, GLfloat> GetBuff();
	void Updata(GLfloat dt);
	void Draw(SpriteRenderer &render);
	void Kill();
	GLboolean Exist();
};
#endif