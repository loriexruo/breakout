#include "interface.h"
Interface::Interface(glm::vec2 Size, Texture2D background) {
	//clear data & memory.
	buttons.clear();
	buttons.swap(std::map<std::string, std::pair<Texture2D, Button>>(buttons));

	this->back = background;
	this->faceSize = Size;
}
void Interface::AddButton(glm::vec2 pos, glm::vec2 size, Texture2D tex, std::string name) {
	Button p(pos, glm::min(pos+size, this->faceSize) - pos);
	this->buttons[name] = std::pair<Texture2D, Button>(tex, p);
}
std::string Interface::GetClick(std::pair<glm::vec2, glm::vec2> sp) {
	glm::vec2 pressPos = sp.first;
	glm::vec2 releasePos = sp.second;
	for (auto p : this->buttons)
		if (p.second.second.IfClick(pressPos, releasePos))
			return p.first;
	return "";
}
void Interface::Draw(SpriteRenderer &render) {
	render.Draw(0, this->back, glm::vec2(0,0), this->faceSize);
	for (auto p : this->buttons) {
		p.second.second.Draw(render, p.second.first);
	}
}