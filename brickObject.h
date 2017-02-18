#ifndef BRICKOBJECT_H
#define BRICKOBJECT_H
#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Texture2D.h"
#include "brickType.h"
#include "spriteRenderer.h"
#include "resourceManager.h"
#include "soundPlayer.h"

#include "myfunc.h"
//save all info of a level.
class BrickObject {
private:
	GLuint linePix, columnPix;//screen_Position(brick's left-top to screen's left-top)
	GLuint Width, Height;//brick's size
	GLuint Type;//brick's type
	GLboolean exist;
public:
	BrickObject(GLuint line = 0, GLuint column = 0, GLuint width = 10, GLuint height = 10, GLuint type = 0);
	GLboolean breakable();
	void hit();
	void Draw(SpriteRenderer &render);
	glm::vec2 Impact(_mycircle p);
};
#endif