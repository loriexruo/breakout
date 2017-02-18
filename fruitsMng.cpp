#include "fruitsMng.h"

std::map<std::string, float>	FruitsManager::bufftime;
std::map<GLuint, Fruit*>		FruitsManager::fruits;
GLuint		FruitsManager::fruitsNum;
glm::vec2	FruitsManager::wndwSize;

void FruitsManager::Clear() {
	//clear data & memory
	FruitsManager::bufftime.clear();
	FruitsManager::bufftime.swap(std::map<std::string, float>(FruitsManager::bufftime));
	FruitsManager::fruits.clear();
	FruitsManager::fruits.swap(std::map<GLuint, Fruit*>(FruitsManager::fruits));

	FruitsManager::fruitsNum = 0;
}
void FruitsManager::Init(glm::vec2 size) {
	FruitsManager::Clear();
	FruitsManager::wndwSize = size;
}
GLboolean FruitsManager::haveBuff(std::string name) {
	GLfloat sp = FruitsManager::bufftime[name];
	if (sp > 0.02) return true;
	return false;
}
void FruitsManager::AddFruit(glm::vec2 pos, glm::vec2 rundirec, GLfloat r, GLfloat time, std::string bufftype) {
	Fruit *p = new Fruit(_mycircle(pos, rundirec, r), ResourceManager::GetTexture(bufftype), bufftype, time);
	FruitsManager::fruits[FruitsManager::fruitsNum] = p;
	FruitsManager::fruitsNum++;
}
void FruitsManager::Updata(GLfloat dt, std::pair<glm::vec2, glm::vec2> line, glm::vec2 normal) {
	for (auto p : FruitsManager::fruits) {
		if (!p.second->Exist()) continue;

		p.second->Updata(dt);
		_mycircle sp = p.second->GetInfo();
		if (sp.pos.y > FruitsManager::wndwSize.y)
			p.second->Kill();
		if (myfunc::collusion_circle_line(sp, line.first, line.second, normal)) {
			std::pair<std::string, GLfloat> gg = p.second->GetBuff();
			FruitsManager::bufftime[gg.first] += gg.second;
			p.second->Kill();
		}
	}
	for (auto p : FruitsManager::bufftime) {
		if (p.second > 0.02)
			FruitsManager::bufftime[p.first] = p.second - dt;
	}
}
void FruitsManager::Draw(SpriteRenderer &render) {
	for (auto p : FruitsManager::fruits) {
		Fruit *sp = p.second;
		if (sp->Exist() == true) 
			sp->Draw(render);
	}
}