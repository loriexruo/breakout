#include "resourceManager.h"

std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;
std::map<GLuint, brickType>			ResourceManager::brickTex;
std::map<GLuint, GLfloat>			ResourceManager::LevelsScore;
Shader ResourceManager::LoadShaderFromFile(const GLchar* vertexPath, const GLchar* geometryPath, const GLchar* fragmentPath, std::string name)
{
	GLuint Program;
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensures ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	try
	{
		// Open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}

	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();
	// 2. Compile shaders
	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];
	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// Print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// Print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Shader Program
	Program = glCreateProgram();
	glAttachShader(Program, vertex);
	glAttachShader(Program, fragment);


	GLuint geometry;
	if (geometryPath != NULL) {
		std::string geometryCode;
		std::ifstream gShaderFile;
		gShaderFile.exceptions(std::ifstream::badbit);
		try {
			gShaderFile.open(geometryPath);
			std::stringstream gShaderStream;
			gShaderStream << gShaderFile.rdbuf();
			gShaderFile.close();
			geometryCode = gShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const GLchar* gShaderCode = geometryCode.c_str();

		geometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry, 1, &gShaderCode, NULL);
		glCompileShader(geometry);
		glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);

		glAttachShader(Program, geometry);
		if (!success) {
			glGetShaderInfoLog(geometry, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}

	glLinkProgram(Program);
	// Print linking errors if any
	glGetProgramiv(Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	if (geometryPath != NULL)
		glDeleteShader(geometry);
	Shader p;
	p.Generate(Program);
	Shaders[name] = p;
	return p;
}
Texture2D ResourceManager::LoadTextureFromFile(const GLchar *texturePath, GLboolean alpha, std::string name) {
	Texture2D p;
	if (alpha) {
		p.Image_Format = GL_RGBA;
		p.Internal_Format = GL_RGBA;
	}
	int width, height;
	unsigned char* image = SOIL_load_image(texturePath, &width, &height, 0, p.Image_Format==GL_RGBA?SOIL_LOAD_RGBA:SOIL_LOAD_RGB);
	p.Generate(width, height, image);
	SOIL_free_image_data(image);
	Textures[name] = p;
	return p;
}
void ResourceManager::LoadBricksType() {
	std::ifstream dat("brickstex.dat");
	while (!dat.eof()) {
		GLuint type;
		std::string x;
		dat >> type >> x;
		if (x == "COLOR") {
			glm::vec3 col;
			dat >> col[0] >> col[1] >> col[2];
			brickTex[type] = brickType(true, col);
		}
		else {
			dat >> x;//texture path
			Texture2D tex = ResourceManager::LoadTextureFromFile(x.c_str(), 1, "");
			brickTex[type] = brickType(false, tex);
		}
	}
}
void ResourceManager::LoadPlayerData() {
	std::ifstream dat("player.dat");
	while (!dat.eof()) {
		GLint level = -1;
		GLfloat score;
		dat >> level >> score;

		if (level == -1) break;

		LevelsScore[level] = score;
	}
}

Shader ResourceManager::GetShader(std::string name) {
	return Shaders[name];
}
Texture2D ResourceManager::GetTexture(std::string name) {
	return Textures[name];
}
brickType ResourceManager::GetBrickType(GLuint type) {
	return brickTex[type];
}
GLfloat ResourceManager::GetLevelScore(GLuint level) {
	GLfloat p = LevelsScore[level];
	if (p > 0.01) return p;
	return -1;
}
GLboolean ResourceManager::UpdScore(GLuint level, GLfloat score) {
	if (LevelsScore[level] > score + 0.1 || LevelsScore[level] < 0.01) {
		LevelsScore[level] = score;
		return true;
	}
	return false;
}
void ResourceManager::End() {
	std::ofstream dat("player.dat");
	for (auto hh : LevelsScore)
		dat << hh.first << " " << hh.second << std::endl;
}
void ResourceManager::Clear() {
	for (auto iter : Shaders)
		glDeleteProgram(iter.second.Program);
	for (auto iter : Textures)
		glDeleteTextures(1, &iter.second.TextureID);
	for (auto iter : brickTex)
		if (iter.second.isColor == false)
			glDeleteTextures(1, &iter.second.tex.TextureID);
}