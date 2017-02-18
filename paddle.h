#pragma once
#ifndef PADDLE_H
#define PADDLE_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "myfunc.h"
#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "fruitsMng.h"
//a paddle's info.
class Paddle {
	glm::vec2 srcSize;
	glm::vec2 paddleSize;
	glm::vec2 paddleCenterPos;
	Texture2D tex;
public:
	Paddle(glm::vec2 screenSize = glm::vec2(0, 0));
	void InitPaddle(glm::vec2 PaddleSize, glm::vec2 PaddleCenterPos, Texture2D texture);
	void Draw(SpriteRenderer &render);
	void move(glm::vec2 moveStep);
	glm::vec2 Impact(_mycircle p);
	//calc the coordinate of the point top of center.
	glm::vec2 getTopCenter();
	std::pair<glm::vec2, glm::vec2> getTopLine();
};
#endif // !PLAYER_H