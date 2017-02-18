#include "Mouse.h"
//input window size and mouse position of the window
Mouse::Mouse(glm::vec2 wndwSize, glm::vec2 mousePos, Texture2D Tex, glm::vec2 msSize) {
	this->windowSize = wndwSize;
	this->wndwpos = mousePos;
	this->tex = Tex;
	this->mouseSize = msSize;
	this->pushPos = glm::vec2(-1, -1);
	this->freePos = glm::vec2(-1, -1);
	this->pushed = false;
	this->setFirst = false;
}
//input mouse position of system
void Mouse::Move(glm::vec2 mousePos) {
	glm::vec2 move;
	if (this->setFirst == false)
		this->setFirst = true;
	else
		move = mousePos - this->lastPos;
	this->lastPos = mousePos;
	this->wndwpos += move;
	this->wndwpos = myfunc::between(this->wndwpos, glm::vec2(0,0), this->windowSize);
}
void Mouse::press() {
	this->pushPos = this->wndwpos;
	this->pushed = true;
}
void Mouse::release() {
	this->freePos = this->wndwpos;
	this->pushed = false;
}
void Mouse::mouseButton(int button, int action) {
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) press();
		if (action == GLFW_RELEASE) release();
	}
}
std::pair<glm::vec2, glm::vec2> Mouse::GetClick() {
	if (this->pushed == true)
		return std::pair<glm::vec2, glm::vec2>(glm::vec2(-1,-1), glm::vec2(-1,-1));
	glm::vec2 a = this->pushPos, b = this->freePos;
	this->pushPos = this->freePos = glm::vec2(-1, -1);
	return std::pair<glm::vec2, glm::vec2>(a, b);
}
void Mouse::Draw(SpriteRenderer &render) {
	glm::vec2 par_pos = this->wndwpos;
	GLfloat tm = glfwGetTime();
	for (int i = 0; i < 50; i++) {
		glm::vec2 s = myfunc::myrand(par_pos, par_pos + glm::vec2(this->mouseSize.x, this->mouseSize.y));
		particleManager::addPraticle(s, glm::vec2(0,-10)+myfunc::myrand(glm::vec2(-5,-5),glm::vec2(5,-5)), tm);
	}
	render.Draw(0, tex, this->wndwpos, this->mouseSize);
}