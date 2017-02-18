#include "fruit.h"
Fruit::Fruit(_mycircle inf, Texture2D Tex, std::string buf, GLfloat tm) {
	this->info = inf;
	this->tex = Tex;
	this->buff = buf;
	this->bufftime = tm;
	this->exist = true;
}
_mycircle Fruit::GetInfo() {
	return this->info;
}
std::pair<std::string, GLfloat> Fruit::GetBuff() {
	return std::pair<std::string, GLfloat>(this->buff, this->bufftime);
}
void Fruit::Updata(GLfloat dt) {
	this->info.pos += this->info.direc * dt;
}
void Fruit::Draw(SpriteRenderer &render) {
	render.Draw(0, this->tex, this->info.pos-glm::vec2(this->info.r), glm::vec2(this->info.r*2));
}
void Fruit::Kill() {
	this->exist = false;
}
GLboolean Fruit::Exist() {
	return this->exist;
}