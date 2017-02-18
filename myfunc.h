#ifndef MYFUNC_H
#define MYFUNC_H
#pragma once

#include <cmath>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "myclass.h"

class myfunc {
private:
	myfunc() {}
public:
	static std::string myitoa(int s);
	//test collusion [circle] [line]
	static GLboolean cross(_mycircle p, glm::vec2 _point1, glm::vec2 _point2);
	static GLboolean collusion_circle_line(_mycircle p, glm::vec2 _point1, glm::vec2 _point2, glm::vec2 Normal);
	//test collusion [circle] [square]
	static glm::vec2 collusion_circle_square(_mycircle p, glm::vec2 _point1, glm::vec2 _point2);
	static glm::vec2 between(glm::vec2 p, glm::vec2 _point1, glm::vec2 _point2);
	static GLboolean IfBetween(glm::vec2 p, glm::vec2 _point1, glm::vec2 _point2);
	static GLfloat myrand(GLfloat _p1, GLfloat _p2);
	static glm::vec2 myrand(glm::vec2 _p1, glm::vec2 _p2);
};
#endif