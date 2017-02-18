#include "particleManager.h"
Shader particleManager::shader;
GLfloat particleManager::particles[PARTICLE_MAX_NUM * 5];
GLuint particleManager::VAO;
GLuint particleManager::VBO;
GLuint particleManager::head;

	void particleManager::Init(Shader p) {
		shader = p;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 5 * PARTICLE_MAX_NUM, nullptr, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2*sizeof(GLfloat)));
		glBindVertexArray(0);
	}
	void particleManager::addPraticle(glm::vec2 pos, glm::vec2 run, GLfloat tm) {
		particles[head * 5] = pos.x;
		particles[head * 5 + 1] = pos.y;
		particles[head * 5 + 2] = run.x;
		particles[head * 5 + 3] = run.y;
		particles[head * 5 + 4] = tm;

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 5*head*sizeof(GLfloat), 5*sizeof(GLfloat), &particles[head*5]);
		glBindVertexArray(0);
		head++;
		if (head == PARTICLE_MAX_NUM)
			head = 0;
	}
	void particleManager::Draw(GLfloat tm) {
		shader.Use();
		shader.Set1f("nowtime", tm);
		glBindVertexArray(VAO);
		glDrawArrays(GL_POINTS, 0, PARTICLE_MAX_NUM);
	}