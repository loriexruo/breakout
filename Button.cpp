#include "Button.h"

Button::Button(glm::vec2 pos, glm::vec2 siz) {
	this->position = pos;
	this->size = siz;
}
GLboolean Button::IfClick(glm::vec2 pressPos, glm::vec2 releasePos) {
	if (myfunc::IfBetween(pressPos, this->position, this->position + this->size) &&
		myfunc::IfBetween(releasePos, this->position, this->position + this->size))
	{
		SoundMng::Play("audio/click.mp3", false);
		return true;
	}
	return false;
}
void Button::Draw(SpriteRenderer &render, Texture2D tex) {
	render.Draw(0, tex, this->position, this->size);
}