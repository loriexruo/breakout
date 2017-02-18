#include "circle.h"
Circle::Circle() {
}
void Circle::Run(GLfloat dt) {
	GLfloat speedUp = 1;
	if (FruitsManager::haveBuff("BUFF_BALL_SPEEDUP"))
		speedUp = 1.2;
	this->CircleCenterPos += dt * speedUp * this->speed * this->runDirec;
}
void Circle::InitCircle(glm::vec2 centerPos, glm::vec2 rundirec, GLfloat r, GLfloat v, Texture2D texture) {
	this->CircleCenterPos = centerPos;
	this->runDirec = glm::normalize(rundirec);
	this->radius = r;
	this->speed = v;
	this->tex = texture;
}
void Circle::reflect(glm::vec2 normal, std::string obj) {
	if (obj == "Brick" && FruitsManager::haveBuff("BUFF_BALL_EROSION"));
	else
		this->runDirec = glm::reflect(this->runDirec, glm::normalize(normal));
}
void Circle::Draw(SpriteRenderer &render) {
	glm::vec2 par_pos = this->CircleCenterPos;
	glm::vec2 tp = glm::vec2(this->radius);
	GLfloat tm = glfwGetTime();
	for (int i = 0; i < 50; i++) {
		glm::vec2 s = myfunc::myrand(par_pos-tp, par_pos+glm::vec2(this->radius,0));
		if (FruitsManager::haveBuff("BUFF_BALL_EROSION"))
			particleManager::addPraticle(s, glm::vec2(0, -10) + myfunc::myrand(glm::vec2(-20, -20), glm::vec2(20, 20)), tm);
		else
			particleManager::addPraticle(s, glm::vec2(0, -10) + myfunc::myrand(glm::vec2(-5, -5), glm::vec2(5, -5)), tm);
	}
	render.Draw(0, this->tex, this->CircleCenterPos - glm::vec2(this->radius), glm::vec2(this->radius*2));
}
void Circle::Rotate(GLfloat angle) {
	glm::mat4 ff;
	ff = glm::rotate(ff, angle, glm::vec3(0, 0, 1));
	glm::vec4 sp = ff * glm::vec4(this->runDirec.x, this->runDirec.y, 0, 1);
	this->runDirec = glm::vec2(sp.x, sp.y);
}
_mycircle Circle::GetInfo() {
	return _mycircle(this->CircleCenterPos, this->runDirec, this->radius);
}
