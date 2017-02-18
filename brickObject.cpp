#include "brickObject.h"

//save all info of a level.

BrickObject::BrickObject(GLuint column, GLuint line, GLuint width, GLuint height, GLuint type) {
	this->columnPix = column;
	this->linePix = line;
	this->Width = width;
	this->Height = height;
	this->Type = type;
	if (Type != 0) //not null.
		this->exist = true;
	else
		this->exist = false;
}
GLboolean BrickObject::breakable() {
	if (this->Type == 1 || this->Type == 0 || this->exist == false) return false;//is solid or null or dead.
	return true;
}
void BrickObject::hit() {
	if (BrickObject::breakable() == true) {
		SoundMng::Play("audio/explosion.wav", false);
		this->exist = false;
	}
}
void BrickObject::Draw(SpriteRenderer &render) {
	if (this->exist == true) {
		brickType p = ResourceManager::GetBrickType(this->Type);
		render.Draw(p.isColor, p.tex, glm::vec2(this->columnPix, this->linePix), glm::vec2(this->Width, this->Height), 0.0f, p.color);
	}
}
glm::vec2 BrickObject::Impact(_mycircle p) {
	glm::vec2 Normal;
	if (this->exist == false)
		return Normal;
	Normal = myfunc::collusion_circle_square(p,
					glm::vec2(this->columnPix, this->linePix), 
					glm::vec2(this->columnPix + this->Width, this->linePix + this->Height));
	if (glm::length(Normal) >= 0.2) {
		BrickObject::hit();
	}
	return Normal;
}