#include "shaderProgram.h"

void Shader::Generate(GLuint s) {
	Program = s;
}
void Shader::Use() const {
	glUseProgram(this->Program);
}
GLuint Shader::sUni(const char *s) const{
	return glGetUniformLocation(Program, s);
}
GLuint Shader::sUniB(const char *s) const{
	return glGetUniformBlockIndex(Program, s);
}
void Shader::SetMat4(const char *s, glm::mat4 p) const {
	this->Use();
	glUniformMatrix4fv(this->sUni(s), 1, GL_FALSE, glm::value_ptr(p));
}
void Shader::SetVec3(const char *s, glm::vec3 p) const {
	this->Use();
	glUniform3f(this->sUni(s), p.x, p.y, p.z);
}
void Shader::SetInt(const char *s, GLint p) const {
	this->Use();
	glUniform1i(this->sUni(s), p);
}
void Shader::Set1f(const char *s, GLfloat p) const {
	this->Use();
	glUniform1f(this->sUni(s), p);
}