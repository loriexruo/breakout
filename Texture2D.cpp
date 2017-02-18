#include "Texture2D.h"

Texture2D::Texture2D() :Width(0), Height(0), Internal_Format(GL_RGBA),
	Image_Format(GL_RGBA), Wrap_S(GL_REPEAT),
	Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR),
	Filter_Max(GL_LINEAR) 
{

}
void Texture2D::Generate(GLuint width, GLuint height, unsigned char *image) {
	Width = width;
	Height = height;
	glGenTextures(1, &this->TextureID);
	glBindTexture(GL_TEXTURE_2D, this->TextureID); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
	glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap_S);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap_T);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter_Max);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture2D::Bind() const {
	glBindTexture(GL_TEXTURE_2D, this->TextureID);
}