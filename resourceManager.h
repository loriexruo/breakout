#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>

#include "shaderProgram.h"
#include "Texture2D.h"
#include "brickObject.h"
class ResourceManager {
private:
	static std::map<std::string, Shader>	Shaders;
	static std::map<std::string, Texture2D> Textures;
	static std::map<GLuint, brickType>		brickTex;
	static std::map<GLuint, std::string>	LevelsPath;
	static std::map<GLuint, GLfloat>		LevelsScore;
	ResourceManager() {}
public:
	static Shader LoadShaderFromFile(const GLchar* vertexPath, const GLchar* geometryPath, const GLchar* fragmentPath, std::string name);
	static Texture2D LoadTextureFromFile(const GLchar *texturePath, GLboolean alpha, std::string name);
	static void LoadBricksType();
	static void LoadPlayerData();
	static Shader GetShader(std::string name);
	static Texture2D GetTexture(std::string name);
	static brickType GetBrickType(GLuint type);
	static GLfloat GetLevelScore(GLuint level);
	static GLboolean UpdScore(GLuint level, GLfloat score);
	static void End();
	static void Clear();//clear things in [GPU].
};
#endif