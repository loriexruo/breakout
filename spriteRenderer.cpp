#include "spriteRenderer.h"

SpriteRenderer::SpriteRenderer(Shader &p) { 
	this->shader = p;
	initRenderData();
}
void SpriteRenderer::initRenderData() {
	GLfloat arr[] = {
		// λ��     // ����
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};
	GLuint spriteVBO;

	glGenVertexArrays(1, &this->spriteVAO);
	glGenBuffers(1, &spriteVBO);

	glBindVertexArray(this->spriteVAO);
	glBindBuffer(GL_ARRAY_BUFFER, spriteVBO);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(arr), arr, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void SpriteRenderer::Draw(GLboolean isColor, Texture2D texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color) {
	//(0,0)�䵽�˾������Ͻ�(position)��λ�á�������Ȼ�ģ�����Ҳ�������ˡ�
	this->shader.Use();
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position, 0.0));//����ƶ���positionλ��

	model = glm::translate(model, glm::vec3(0.5*size.x, 0.5*size.y, 0.0));//Ȼ��λ
	model = glm::rotate(model, rotate, glm::vec3(0,0,1));//Ȼ����ת
	model = glm::translate(model, glm::vec3(-0.5*size.x, -0.5*size.y, 0.0));//�ѷ��������ƶ���ԭ��

	model = glm::scale(model, glm::vec3(size, 1.0));
	this->shader.SetMat4("model", model);

	this->shader.SetVec3("spriteColor", color);
	this->shader.SetInt("isColor", (GLint)isColor);
	this->shader.SetInt("image", 0);
	if (isColor == 0) {
		glActiveTexture(GL_TEXTURE0);
		texture.Bind();
	}
	glBindVertexArray(this->spriteVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}