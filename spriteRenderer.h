#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H
#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture2D.h"
#include "shaderProgram.h"
class SpriteRenderer {
public:
	SpriteRenderer(Shader &p);
	~SpriteRenderer() {}

	void Draw(GLboolean isColor, Texture2D texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10),
		GLfloat rotate = 0.0, glm::vec3 color = glm::vec3(1.0f));
private:
	Shader shader;
	GLuint spriteVAO;

	void initRenderData();
};
#endif
