#include "UberGame.h"

const glm::ivec2 PLAYER_SIZE(100, 20);
const glm::vec2 MOVE_SPEED(500, 000);
const GLfloat CIRCLE_SPEED(400.0f);
const GLfloat CIRCLE_RADIUS(10.0f);

Game::Game(GLuint width, GLuint height) {
	this->State = GAME_MENU;
	this->Width = width;
	this->Height = height;
	this->levels = 0;
	this->shouldClose = false;
}
Game::~Game() {

}
GLboolean Game::ShouldClose() {
	return this->shouldClose;
}
GLboolean Game::ImpactWithEdge(Circle *circle) {
	_mycircle p = circle->GetInfo();
	glm::vec2 Normal;
	Normal = myfunc::collusion_circle_square(p, glm::vec2(-100, 0), glm::vec2(0, this->Height));
	if (glm::length(Normal) >= 0.2) {
		circle->reflect(Normal, "Edge");
		return true;
	}
	Normal = myfunc::collusion_circle_square(p, glm::vec2(0, -100), glm::vec2(this->Width, 0));
	if (glm::length(Normal) >= 0.2) {
		circle->reflect(Normal, "Edge");
		return true;
	}
	Normal = myfunc::collusion_circle_square(p, glm::vec2(this->Width, 0), glm::vec2(this->Width + 100, this->Height));
	if (glm::length(Normal) >= 0.2) {
		circle->reflect(Normal, "Edge");
		return true;
	}
	return false;
}
GLboolean Game::ImpactWithBricks(Circle *circle, LevelObject *lev) {
	glm::vec2 normal = lev->Impact(circle->GetInfo());
	if (glm::length(normal) >= 0.2) {
		circle->reflect(normal, "Brick");
		return true;
	}
	return false;
}
GLboolean Game::ImpactWithPaddle(Circle *circle, Paddle *pad) {
	glm::vec2 normal = pad->Impact(circle->GetInfo());
	if (glm::length(normal) >= 0.2) {
		circle->reflect(normal, "Paddle");
		if (this->Keys[GLFW_KEY_LEFT] && !this->Keys[GLFW_KEY_RIGHT])
			circle->Rotate(-10);
		if (!this->Keys[GLFW_KEY_LEFT] && this->Keys[GLFW_KEY_RIGHT])
			circle->Rotate(10);
		return true;
	}
	return false;
}
void Game::ImpactTest(Circle *circle) {
	if (ImpactWithEdge(circle)) return;
	if (ImpactWithBricks(circle, this->slevel)) return;
	if (ImpactWithPaddle(circle, this->spaddle)) return;
}

void Game::LoadLevel(int level) {
	this->slevel->load(level, this->Width, this->Height / 2);
	this->spaddle->InitPaddle(PLAYER_SIZE, glm::vec2(this->Width / 2, this->Height - PLAYER_SIZE.y / 2), ResourceManager::GetTexture("paddle"));
	this->playerCircle->InitCircle(glm::vec2(this->Width / 2, this->Height - PLAYER_SIZE.y / 2) - glm::vec2(-CIRCLE_RADIUS, 0),
		glm::vec2(0.3, -1), CIRCLE_RADIUS, CIRCLE_SPEED, ResourceManager::GetTexture("circle"));
	FruitsManager::Init(glm::vec2(this->Width, this->Height));
	levelTime = 0;
	newScore = false;
}

void Game::Init() {
	ResourceManager::LoadShaderFromFile("shaders/sprite.vs", nullptr, "shaders/sprite.frag", "sprite");
	ResourceManager::LoadShaderFromFile("shaders/text.vs", nullptr, "shaders/text.frag", "text");
	ResourceManager::LoadShaderFromFile("shaders/particle.vs", nullptr, "shaders/particle.frag", "particle");
	// 配置着色器
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
		static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);

	ResourceManager::GetShader("sprite").SetMat4("projection", projection);

	ResourceManager::GetShader("text").SetMat4("projection", projection);

	ResourceManager::GetShader("particle").SetMat4("projection", projection);

	//配置音频引擎
	SoundMng::Init();
	SoundMng::Play("audio/backgroundmusic.mp3", true);
	
	//设置专门输出文字的控制
	printer = new TextPrinter(ResourceManager::GetShader("text"));
	//设置专用于渲染的控制
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	//设置专用于粒子渲染的控制
	particleManager::Init(ResourceManager::GetShader("particle"));

	// 加载纹理
	ResourceManager::LoadTextureFromFile("textures/menu_background.png", GL_TRUE, "menu_background");
	ResourceManager::LoadTextureFromFile("textures/menu_start_game.png", GL_TRUE, "menu_start_game");
	ResourceManager::LoadTextureFromFile("textures/menu_quit_game.png", GL_TRUE, "menu_quit_game");

	ResourceManager::LoadTextureFromFile("textures/pause_background.png", GL_TRUE, "pause_background");
	ResourceManager::LoadTextureFromFile("textures/pause_continuegame.png", GL_TRUE, "pause_continuegame");
	ResourceManager::LoadTextureFromFile("textures/pause_backtomenu.png", GL_TRUE, "pause_backtomenu");

	ResourceManager::LoadTextureFromFile("textures/fail_background.png", GL_TRUE, "fail_background");
	ResourceManager::LoadTextureFromFile("textures/fail_tryagain.png", GL_TRUE, "fail_tryagain");
	ResourceManager::LoadTextureFromFile("textures/fail_backtomenu.png", GL_TRUE, "fail_backtomenu");

	ResourceManager::LoadTextureFromFile("textures/win_background.png", GL_TRUE, "win_background");
	ResourceManager::LoadTextureFromFile("textures/win_nextlevel.png", GL_TRUE, "win_nextlevel");
	ResourceManager::LoadTextureFromFile("textures/win_tryagain.png", GL_TRUE, "win_tryagain");
	ResourceManager::LoadTextureFromFile("textures/win_backtomenu.png", GL_TRUE, "win_backtomenu");

	ResourceManager::LoadTextureFromFile("textures/mouse.png", GL_TRUE, "mouse");
	ResourceManager::LoadTextureFromFile("textures/background.png", GL_TRUE, "background");
	ResourceManager::LoadTextureFromFile("textures/paddle.png", GL_TRUE, "paddle");
	ResourceManager::LoadTextureFromFile("textures/huaji.png", GL_TRUE, "circle");

	ResourceManager::LoadTextureFromFile("textures/BUFF_PADDLE_DOUBLELENGTH.png", GL_TRUE, "BUFF_PADDLE_DOUBLELENGTH");
	ResourceManager::LoadTextureFromFile("textures/BUFF_BALL_EROSION.png", GL_TRUE, "BUFF_BALL_EROSION");
	ResourceManager::LoadTextureFromFile("textures/BUFF_BALL_SPEEDUP.png", GL_TRUE, "BUFF_BALL_SPEEDUP");

	//加载bricks
	ResourceManager::LoadBricksType();
	//加载玩家数据
	ResourceManager::LoadPlayerData();
	for (int i = 0; i <= LEVEL_MAX_NUM; i++) {
		GLfloat tm = ResourceManager::GetLevelScore(i);
		if (tm < 0) {
			this->levels = i;
			break;
		}
	}
	//创建menu界面
	menu = new Interface(glm::vec2(this->Width, this->Height), ResourceManager::GetTexture("menu_background"));
	menu->AddButton(glm::vec2(500, 200), glm::vec2(200, 50), ResourceManager::GetTexture("menu_start_game"), "menu_start_game");
	menu->AddButton(glm::vec2(500, 300), glm::vec2(200, 50), ResourceManager::GetTexture("menu_quit_game"), "menu_quit_game");
	//创建pause界面
	pause = new Interface(glm::vec2(this->Width, this->Height), ResourceManager::GetTexture("pause_background"));
	pause->AddButton(glm::vec2(280, 450), glm::vec2(100, 50), ResourceManager::GetTexture("pause_continuegame"), "pause_continuegame");
	pause->AddButton(glm::vec2(420, 450), glm::vec2(100, 50), ResourceManager::GetTexture("pause_backtomenu"), "pause_backtomenu");
	//创建失败界面
	fail = new Interface(glm::vec2(this->Width, this->Height), ResourceManager::GetTexture("fail_background"));
	fail->AddButton(glm::vec2(280, 450), glm::vec2(100, 50), ResourceManager::GetTexture("fail_tryagain"), "fail_tryagain");
	fail->AddButton(glm::vec2(420, 450), glm::vec2(100, 50), ResourceManager::GetTexture("fail_backtomenu"), "fail_backtomenu");
	//创建成功界面
	win = new Interface(glm::vec2(this->Width, this->Height), ResourceManager::GetTexture("win_background"));
	win->AddButton(glm::vec2(280, 360), glm::vec2(240, 50), ResourceManager::GetTexture("win_nextlevel"), "win_nextlevel");
	win->AddButton(glm::vec2(280, 450), glm::vec2(100, 50), ResourceManager::GetTexture("win_tryagain"), "win_tryagain");
	win->AddButton(glm::vec2(420, 450), glm::vec2(100, 50), ResourceManager::GetTexture("win_backtomenu"), "win_backtomenu");

	//创建鼠标程序
	mouse = new Mouse(glm::vec2(this->Width, this->Height), glm::vec2(this->Width/2, this->Height/2), ResourceManager::GetTexture("mouse"));
	//创建关卡
	this->slevel = new LevelObject;
	//创建paddle
	this->spaddle = new Paddle(glm::vec2(this->Width, this->Height));
	//创建circle
	this->playerCircle = new Circle;
	//创建果实管理
	FruitsManager::Init(glm::vec2(this->Width, this->Height));
}
//update game's state by mouse & keyboard
void Game::ProcessInput(GLfloat dt) {
	switch (this->State) {
		case GAME_MENU : {
			std::string p = this->menu->GetClick(this->mouse->GetClick());
			if (p == "menu_quit_game")
				this->shouldClose = true;
			if (p == "menu_start_game") {
				LoadLevel(this->levels);
				this->State = GAME_READY;
			}
			break;
		}
		case GAME_READY: {
			glm::vec2 move = dt * MOVE_SPEED;
			if (this->Keys[GLFW_KEY_LEFT])		this->spaddle->move(glm::vec2(-move.x, 0));
			if (this->Keys[GLFW_KEY_RIGHT])		this->spaddle->move(glm::vec2(move.x, 0));
			if (this->Keys[GLFW_KEY_UP])		this->spaddle->move(glm::vec2(0, -move.y));
			if (this->Keys[GLFW_KEY_DOWN])		this->spaddle->move(glm::vec2(0, move.y));

			this->playerCircle->InitCircle(this->spaddle->getTopCenter() - glm::vec2(0, CIRCLE_RADIUS),
				glm::vec2(0.3, -1), CIRCLE_RADIUS, CIRCLE_SPEED, ResourceManager::GetTexture("circle"));
			if (this->Keys[GLFW_KEY_SPACE])
				this->State = GAME_ACTIVE;
			break;
		}
		case GAME_ACTIVE: {
			glm::vec2 move = dt * MOVE_SPEED;
			if (this->Keys[GLFW_KEY_LEFT])		this->spaddle->move(glm::vec2(-move.x, 0));
			if (this->Keys[GLFW_KEY_RIGHT])		this->spaddle->move(glm::vec2(move.x, 0));
			if (this->Keys[GLFW_KEY_UP])		this->spaddle->move(glm::vec2(0, -move.y));
			if (this->Keys[GLFW_KEY_DOWN])		this->spaddle->move(glm::vec2(0, move.y));

			if (this->Escape.first) {
				this->Escape.first = false;
				if (this->Escape.second == GAME_ACTIVE)
					this->State = GAME_PAUSE;
			}
			break;
		}
		case GAME_PAUSE: {
			if (this->Escape.first) {
				this->Escape.first = false;
				if (this->Escape.second == GAME_PAUSE)
					this->State = GAME_ACTIVE;
			}
			std::string p = this->pause->GetClick(this->mouse->GetClick());
			if (p == "pause_continuegame")
				this->State = GAME_ACTIVE;
			if (p == "pause_backtomenu")
				this->State = GAME_MENU;
			break;
		}
		case GAME_WIN: {
			if (this->Escape.first) {
				this->Escape.first = false;
				if (this->Escape.second == GAME_WIN)
					this->State = GAME_MENU;
			}
			std::string p = this->win->GetClick(this->mouse->GetClick());
			if (p == "win_nextlevel") {
				if (this->levels == LEVEL_MAX_NUM) {
					SoundMng::RemoveAll();
					SoundMng::Play("audio/breakout.mp3", true);
					this->State = GAME_BREAKDOWN;
				}
				else {
					this->State = GAME_READY;
					levels++;
					LoadLevel(levels);
				}
			}
			if (p == "win_tryagain") {
				this->State = GAME_READY;
				LoadLevel(levels);
			}
			if (p == "win_backtomenu")
				this->State = GAME_MENU;
			break;
		}
		case GAME_FAIL: {
			if (this->Escape.first) {
				this->Escape.first = false;
				if (this->Escape.second == GAME_FAIL)
					this->State = GAME_MENU;
			}
			std::string p = this->fail->GetClick(this->mouse->GetClick());
			if (p == "fail_tryagain") {
				this->State = GAME_READY;
				LoadLevel(levels);
			}
			if (p == "fail_backtomenu")
				this->State = GAME_MENU;
			break;
		}
		case GAME_BREAKDOWN: {
			if (this->Escape.first) {
				this->Escape.first = false;
				if (this->Escape.second == GAME_BREAKDOWN) {
					SoundMng::RemoveAll();
					SoundMng::Play("audio/backgroundmusic.mp3", true);
					this->State = GAME_MENU;
				}
			}
			break;
		}
	}
}
//Updata game's state by time.
void Game::Update(GLfloat dt) {
	if (this->State == GAME_ACTIVE) {
		levelTime += dt;

		if (dt > myfunc::myrand(0.0, 10))//大概5s一个fruit
			this->addFruit();

		ImpactTest(this->playerCircle);

		this->playerCircle->Run(dt);

		FruitsManager::Updata(dt, this->spaddle->getTopLine(), glm::vec2(0, -1));

		if (this->slevel->allBricksCleared()) {
			newScore = ResourceManager::UpdScore(this->levels, this->levelTime);
			this->State = GAME_WIN;
		}
		if (circleOut())
			this->State = GAME_FAIL;
	}
}
void Game::Render() {
	if (this->State == GAME_MENU) {
		this->menu->Draw(*this->Renderer);
		particleManager::Draw(glfwGetTime());
		this->mouse->Draw(*this->Renderer);
	}
	else if (this->State == GAME_READY || this->State == GAME_ACTIVE) {
		this->Renderer->Draw(false, ResourceManager::GetTexture("background"), glm::vec2(0,0), glm::vec2(this->Width, this->Height), 0.0f, glm::vec3(1));
		this->slevel->Draw(*this->Renderer);
		this->spaddle->Draw(*this->Renderer);
		FruitsManager::Draw(*this->Renderer);
		particleManager::Draw(glfwGetTime());
		this->playerCircle->Draw(*this->Renderer);

		this->ShowLevelInfo();
		if (this->State == GAME_READY)
			this->printer->RenderText("Press Blankspace to shoot your ball", 200, 500, 0.5, glm::vec3(0, 0, 0));
		if (this->State == GAME_ACTIVE)	
			this->printer->RenderText("Press Esc to pause", 0, 570, 0.7, glm::vec3(0, 0, 0));
	}
	else if (this->State == GAME_PAUSE) {
		this->pause->Draw(*this->Renderer);
		particleManager::Draw(glfwGetTime());
		this->mouse->Draw(*this->Renderer);
	}
	else if (this->State == GAME_FAIL) {
		this->fail->Draw(*this->Renderer);
		particleManager::Draw(glfwGetTime());
		this->mouse->Draw(*this->Renderer);
	}
	else if (this->State == GAME_WIN) {
		this->win->Draw(*this->Renderer);

		if (newScore)	this->printer->RenderText("New Score!", 50, 350, 1, glm::vec3(1,0,0));
		this->printer->RenderText("Best Score:" + myfunc::myitoa(ResourceManager::GetLevelScore(levels)) + "s", 50, 400, 0.5, glm::vec3(0));

		particleManager::Draw(glfwGetTime());
		this->mouse->Draw(*this->Renderer);
	}
	else if (this->State == GAME_BREAKDOWN) {
		this->printer->RenderText("Congratulations!", 100, 100, 1, glm::vec3(1,0,0));
		this->printer->RenderText("Thank you for playing!", 100, 200, 0.5, glm::vec3(1));
		this->printer->RenderText("Game developer: std::pair<laji, juruo> loriex" , 100, 300, 0.5, glm::vec3(1));
		this->printer->RenderText("Press ESC to menu", 300, 400, 0.5, glm::vec3(1));
		particleManager::Draw(glfwGetTime());
		this->mouse->Draw(*this->Renderer);
	}
}
//save player's data.
void Game::End() {
	ResourceManager::End();
}
void Game::addFruit() {
	int type = rand() % 10 + 1;
	glm::vec2 _p1(0, 0), _p2(this->Width, this->Height / 2);
	glm::vec2 _pos = myfunc::myrand(_p1, _p2);
	std::string buff_type;
	if (type <= 4)		buff_type = "BUFF_PADDLE_DOUBLELENGTH";
	else if (type <= 6) buff_type = "BUFF_BALL_EROSION";
	else				buff_type = "BUFF_BALL_SPEEDUP";
	FruitsManager::AddFruit(_pos, glm::vec2(0,100), 20.0, 5.0, buff_type);
}
GLboolean Game::circleOut() {
	_mycircle p = playerCircle->GetInfo();
	if (p.pos.y >= this->Height)
		return true;
	return false;
}
void Game::key_callback(int key, int action) {
	if (key <= 1024 && key >= 0) {
		if (key == GLFW_KEY_ESCAPE) {
			if (action == GLFW_RELEASE)
				this->Escape = std::pair<GLboolean, GameState>(GL_TRUE, this->State);
		}
		else {
			if (action == GLFW_PRESS)
				this->Keys[key] = GL_TRUE;
			else if (action == GLFW_RELEASE)
				this->Keys[key] = GL_FALSE;
		}
	}
}
void Game::moveMouse(glm::vec2 mousePos) {
	this->mouse->Move(mousePos);
}
void Game::mouseButton(int button, int action) {
	this->mouse->mouseButton(button, action);
}
void Game::ShowLevelInfo() {
	this->printer->RenderText("level:" + myfunc::myitoa(levels), 0, 20, 0.5, glm::vec3(0));
	this->printer->RenderText("time: " + myfunc::myitoa(int(this->levelTime)), 0, 40, 0.5, glm::vec3(0));
}