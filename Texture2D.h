#ifndef TEXTURE2D_H
#define TEXTURE2D_H
#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class Texture2D {
public:
	Texture2D();

	GLuint TextureID, Width, Height;
	GLuint Internal_Format, Image_Format;
	GLuint Wrap_S, Wrap_T;
	GLuint Filter_Min, Filter_Max;
	void Generate(GLuint width, GLuint height, unsigned char *textureID);
	void Bind() const;
};
#endif