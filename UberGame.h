#ifndef UBERGAME_H
#define UBERGAME_H
#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <irrklang/irrKlang.h>

#include "resourceManager.h"

#include "spriteRenderer.h"
#include "text.h"
#include "particleManager.h"

#include "soundPlayer.h"

#include "levelObject.h"
#include "paddle.h"
#include "fruitsMng.h"
#include "circle.h"

#include "myclass.h"
#include "myfunc.h"

#include "Mouse.h"
#include "interface.h"

#define LEVEL_MAX_NUM 6
enum GameState {
	GAME_MENU,
	GAME_READY,
	GAME_ACTIVE,
	GAME_PAUSE,
	GAME_WIN,
	GAME_FAIL,
	GAME_BREAKDOWN
};
class Game {
public:
	GLboolean shouldClose;

	SpriteRenderer  *Renderer;
	TextPrinter *printer;

	GLuint levels;
	GLboolean newScore;
	GLfloat levelTime;
	LevelObject *slevel;
	Circle *playerCircle;
	Paddle *spaddle;

	GameState State;
	Interface *menu, *pause, *fail, *win;

	Mouse *mouse;
	std::pair<GLboolean, GameState> Escape;
	GLboolean Keys[1024];
	

	GLuint Width, Height;
	Game(GLuint width, GLuint height);
	~Game();
	GLboolean ShouldClose();
	//Add all shader/texture/Level/player info
	void Init();
	//respond all button
	void ProcessInput(GLfloat dt);
	//update status
	void Update(GLfloat dt);
	//get status and render a picture
	void Render();
	void End();

	GLboolean ImpactWithEdge(Circle *circle);
	GLboolean ImpactWithBricks(Circle *circle, LevelObject *lev);
	GLboolean ImpactWithPaddle(Circle *circle, Paddle *pad);
	void ImpactTest(Circle *circle);
	void addFruit();
	GLboolean circleOut();
	void LoadLevel(int level);
	void key_callback(int key, int action);
	void moveMouse(glm::vec2 mousePos);
	void mouseButton(int button, int action);
	void ShowLevelInfo();
};
#endif // UBERGAME_H
