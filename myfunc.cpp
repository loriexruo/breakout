#include "myfunc.h"

//turn a unsigned int to a string
std::string myfunc::myitoa(int s) {
	char hh[10];
	_itoa_s(s, hh, 10);
	std::string f = hh;
	return f;
}
//test collusion [circle] [line]
GLboolean myfunc::cross(_mycircle p, glm::vec2 _point1, glm::vec2 _point2) {
	if (glm::length(p.pos - _point1) < p.r) return true;
	if (glm::length(p.pos - _point2) < p.r) return true;
	glm::vec2 _f = _point2 - _point1;
	glm::vec2 _u = glm::normalize(_f);
	glm::vec2 _t = p.pos - _point1;
	glm::vec2 _v = _t - glm::dot(_u, _t) * _u;
	glm::vec2 _coord(glm::dot(_u, _t), glm::length(_v));
	if (_coord.x >= 0 && _coord.x <= glm::length(_f) && _coord.y < p.r) return true;
	return false;
}
GLboolean myfunc::collusion_circle_line(_mycircle p, glm::vec2 _point1, glm::vec2 _point2, glm::vec2 Normal) {
	if (cross(p, _point1, _point2) && glm::dot(p.direc, Normal) < 0)
		return true;
	return false;
}
//test collusion [circle] [square]
glm::vec2 myfunc::collusion_circle_square(_mycircle p, glm::vec2 _point1, glm::vec2 _point2) {
	glm::vec2 minPoint = glm::vec2(glm::min(_point1.x, _point2.x), glm::min(_point1.y, _point2.y));
	glm::vec2 maxPoint = glm::vec2(glm::max(_point1.x, _point2.x), glm::max(_point1.y, _point2.y));
	if (collusion_circle_line(p, minPoint, glm::vec2(minPoint.x, maxPoint.y), glm::vec2(-1, 0)))	return glm::vec2(-1, 0);
	if (collusion_circle_line(p, minPoint, glm::vec2(maxPoint.x, minPoint.y), glm::vec2(0, -1)))	return glm::vec2(0, -1);
	if (collusion_circle_line(p, maxPoint, glm::vec2(minPoint.x, maxPoint.y), glm::vec2(0, 1)))		return glm::vec2(0, 1);
	if (collusion_circle_line(p, maxPoint, glm::vec2(maxPoint.x, minPoint.y), glm::vec2(1, 0)))		return glm::vec2(1, 0);
	return glm::vec2(0, 0);
}
glm::vec2 myfunc::between(glm::vec2 p, glm::vec2 _point1, glm::vec2 _point2) {
	return glm::min(glm::max(p, _point1), _point2);
}
GLboolean myfunc::IfBetween(glm::vec2 p, glm::vec2 _point1, glm::vec2 _point2) {
	if (p.x <= _point2.x && p.y <= _point2.y && 
		p.x >= _point1.x && p.y >= _point1.y) 
		return true;
	return false;
}
GLfloat myfunc::myrand(GLfloat _p1, GLfloat _p2) {
	if (_p1 > _p2) return myrand(_p2, _p1);
	return _p1 + (_p2 - _p1) * (1.0*(rand() % 30000)/30000);
}
glm::vec2 myfunc::myrand(glm::vec2 _p1, glm::vec2 _p2) {
	return glm::vec2(myrand(_p1.x, _p2.x), myrand(_p1.y, _p2.y));
}