#include "levelObject.h"

void LevelObject::load(GLuint levels, GLuint LinePix, GLuint ColumnPix) {
	//empty data & memory.
	bricks.clear();
	std::vector<BrickObject*>(bricks).swap(bricks);

	std::string path = "levels/" + myfunc::myitoa(levels) + ".level";
	std::fstream dat(path);
	dat >> this->columns >> this->lines;
	GLuint type;
	GLuint oneWidth, oneHeight;
	oneWidth = LinePix / this->columns;
	oneHeight = ColumnPix / this->lines;
	for (GLuint i = 0; i < this->lines; i++) {
		for (GLuint j = 0; j < this->columns; j++) {
			dat >> type;
			bricks.push_back(new BrickObject(j*oneWidth, i*oneHeight, oneWidth, oneHeight, type));
		}
	}
}
void LevelObject::Draw(SpriteRenderer &render) {
	for (auto hh : bricks)
		hh->Draw(render);
}
glm::vec2 LevelObject::Impact(_mycircle p) {
	glm::vec2 Normal(0, 0);
	for (auto hh : bricks) {
		Normal = hh->Impact(p);
		if (glm::length(Normal) >= 0.2)
			return Normal;
	}
	return Normal;
}
GLboolean LevelObject::allBricksCleared() {
	for (auto hh : bricks)
		if (hh->breakable()) return false;
	return true;
}