#include "paddle.h"

//a paddle's info.
Paddle::Paddle(glm::vec2 screenSize) {
	this->srcSize = screenSize;
}
void Paddle::InitPaddle(glm::vec2 PaddleSize, glm::vec2 PaddleCenterPos, Texture2D texture) {
	this->paddleSize = PaddleSize;
	this->paddleCenterPos = PaddleCenterPos;
	this->tex = texture;
}
void Paddle::Draw(SpriteRenderer &render) {
	glm::vec2 sp(this->paddleSize.x / 2, this->paddleSize.y / 2);
	if (FruitsManager::haveBuff("BUFF_PADDLE_DOUBLELENGTH"))
		sp = glm::vec2(sp.x*2, sp.y);
	render.Draw(0, tex, this->paddleCenterPos-sp, glm::vec2(sp.x*2, sp.y*2));
}
void Paddle::move(glm::vec2 moveStep) {
	this->paddleCenterPos += moveStep;
	glm::vec2 sp(this->paddleSize.x / 2, this->paddleSize.y / 2);
	if (FruitsManager::haveBuff("BUFF_PADDLE_DOUBLELENGTH"))
		sp = glm::vec2(sp.x * 2, sp.y);
	this->paddleCenterPos = myfunc::between(this->paddleCenterPos, sp, this->srcSize - sp);
}
glm::vec2 Paddle::Impact(_mycircle p) {
	std::pair<glm::vec2, glm::vec2> sp = Paddle::getTopLine();
	if (myfunc::collusion_circle_line(p, sp.first, sp.second, glm::vec2(0, -1)))
		return glm::vec2(0, -1);
	return glm::vec2(0,0);
}
glm::vec2 Paddle::getTopCenter() {
	return glm::vec2(this->paddleCenterPos - glm::vec2(0, this->paddleSize.y/2));
}
std::pair<glm::vec2, glm::vec2> Paddle::getTopLine() {
	glm::vec2 sp(this->paddleSize.x / 2, this->paddleSize.y / 2);
	if (FruitsManager::haveBuff("BUFF_PADDLE_DOUBLELENGTH"))
		sp = glm::vec2(sp.x * 2, sp.y);
	return std::pair<glm::vec2, glm::vec2>(this->paddleCenterPos-sp, this->paddleCenterPos+glm::vec2(sp.x, -sp.y));
}