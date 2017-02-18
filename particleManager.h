#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H
#pragma once
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderProgram.h"
#define PARTIUCLE_LIFE 1
#define PARTICLE_MAX_NUM 10000

class particleManager {
private:
	static Shader shader;
	static GLfloat particles[PARTICLE_MAX_NUM * 5];
	static GLuint head, VAO, VBO;
	particleManager() {}
public:
	static void Init(Shader p);
	static void addPraticle(glm::vec2 pos, glm::vec2 run, GLfloat tm);
	static void Draw(GLfloat tm);
};
#endif