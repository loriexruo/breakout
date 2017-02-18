#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
#include <map>
#pragma comment (lib, "glfw3.lib")
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glew32s.lib")
#pragma comment (lib, "SOIL.lib")
#pragma comment (lib, "freetyped.lib")
#pragma comment(lib, "irrKlang.lib")
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <irrklang/irrKlang.h>

#include "UberGame.h"
#include "resourceManager.h"
#include "spriteRenderer.h"
#include "levelObject.h"
#include "brickObject.h"
#include "brickType.h"
#include "soundPlayer.h"
#include "paddle.h"
#include "circle.h"
#include "fruitsMng.h"
#include "shaderProgram.h"
#include "myclass.h"
#include "myfunc.h"

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void mousePos_callback(GLFWwindow *window, double xpos, double ypos);
void mouseButton_callback(GLFWwindow *window, int button, int action, int mod);
const GLuint SCREEN_WIDTH = 800;
const GLuint SCREEN_HEIGHT = 600;

Game BreakOut(SCREEN_WIDTH, SCREEN_HEIGHT);

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BreakOut", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mousePos_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetMouseButtonCallback(window, mouseButton_callback);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	glGetError();//dissert glewInit() bug.

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST); 
	glEnable(GL_PROGRAM_POINT_SIZE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	BreakOut.Init();
	//ResourceManager::GetShader("spriteShader");
	GLfloat lstTime = glfwGetTime(), nowTime, deltaTime;
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		if (BreakOut.ShouldClose() == true)
			glfwSetWindowShouldClose(window, GL_TRUE);

		nowTime = glfwGetTime();
		deltaTime = nowTime - lstTime;
		lstTime = nowTime;

		BreakOut.ProcessInput(deltaTime);
		BreakOut.Update(deltaTime);

		glClearColor(0,0,0,1);
		glClear(GL_COLOR_BUFFER_BIT);
		BreakOut.Render();

		glfwSwapBuffers(window);

		GLint err = glGetError();
		if (err) printf("GetError: %d\n", err);
	}
	BreakOut.End();
	glfwTerminate();
	return 0;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	BreakOut.key_callback(key, action);
}
void mousePos_callback(GLFWwindow *window, double xpos, double ypos) {
	BreakOut.moveMouse(glm::vec2(xpos, ypos));
}
void mouseButton_callback(GLFWwindow *window, int button, int action, int mod) {
	BreakOut.mouseButton(button, action);
}