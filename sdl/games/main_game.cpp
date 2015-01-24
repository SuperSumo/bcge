#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "main_game.h"
#include "../input.h"
#include "../manager.h"
#include "../window.h"

MainGame::MainGame(Manager* manager):
	Game(manager), _fov(45.0f), _nearView(0.1f), _farView(100.0f),
	_rotV(glm::vec3(2,3,1)), _pos(glm::vec3(0,0,-4))
{
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "MainGame::MainGame()");

	// Create buffers
	_vbo = new Buffer(VBO, GL_FLOAT);
	_cbo = new Buffer(CBO, GL_FLOAT);
	_ibo = new Buffer(IBO, GL_UNSIGNED_INT);
}

MainGame::~MainGame()
{
	delete _vbo;
	delete _cbo;
	delete _ibo;
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "MainGame::~MainGame()");
}

bool MainGame::init()
{
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "MainGame::init()");

	// Create an Input
	if (_input)
		delete _input;
	_input = new Input(this);

	// Register all the callbacks
	_input->register_callback("attack", attack);
	_input->register_callback("menu_click", menu_click);
	_input->register_callback("jump", jump);
	_input->register_callback("quit", quit);
	_input->register_callback("toggle_menu", toggle_menu);
	_input->register_callback("crouch", crouch);
	_input->register_callback("toggle_fullscreen", toggle_fullscreen);

	// Initialize the input, which loads the keymap from config.json
	_input->init();

	// Load the main keymap into the input stack
	// _input->push("menu");
	_input->push("main");

	// By default, hide the cursor in this game mode
	SDL_ShowCursor(0);

	// Since we are hiding the cursor, set to relative mode
	SDL_SetRelativeMouseMode(SDL_TRUE);

	// Load the model data.
	// TODO: Delete all of this and move into a game loading thing.

	/* A cube's vertices
	 *    7----6
	 *   /|   /|
	 *  1----2 |  y  z
	 *  | 4--|-5  | /
	 *  |/   |/   |/
	 *  0----3    o----x
	 */

	GLfloat vertices[] =
	{
		-0.25f,	-0.25f,	-0.25f,	// 0
		-0.25f,	0.25f,	-0.25f,	// 1
		0.25f,	0.25f,	-0.25f,	// 2
		0.25f,	-0.25f,	-0.25f,	// 3
		-0.25f,	-0.25f,	0.25f,	// 4
		0.25f,	-0.25f,	0.25f,	// 5
		0.25f,	0.25f,	0.25f,	// 6
		-0.25f,	0.25f,	0.25f	// 7
	};

	GLfloat colors[] =
	{
		0,0,0,0.5f,	// 0
		0,1,0,0.5f,	// 1
		1,1,0,0.5f,	// 2
		1,0,0,0.5f,	// 3
		0,0,1,0.5f,	// 4
		1,0,1,0.5f,	// 5
		1,1,1,0.5f,	// 6
		0,1,1,0.5f	// 7
	};

	GLuint indices[] =
	{
		0,1,2, 0,2,3,	// Front
		4,5,6, 4,6,7,	// Back
		4,7,1, 4,1,0,	// Left
		3,2,6, 3,6,5,	// Right
		1,7,6, 1,6,2,	// Top
		5,4,0, 5,0,3	// Bottom
	};

	bool allGood = true;
	allGood &= _vbo->load(vertices, sizeof(vertices));
	allGood &= _cbo->load(colors, sizeof(colors));
	allGood &= _ibo->load(indices, sizeof(indices));

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
		"MainGame::init() - Buffers Loaded? %i", allGood);
	if (!allGood)
		_manager->quit();

	// Clear out the shaderManager
	shaderManager.clear();

	// Load the shaders
	shaderManager.add_shader(GL_VERTEX_SHADER, "shaders/vertex.glsl");
	shaderManager.add_shader(GL_FRAGMENT_SHADER, "shaders/fragment.glsl");

	// Load the shaderProgs
	StringVec shaderNames;
	shaderNames.push_back("shaders/vertex.glsl");
	shaderNames.push_back("shaders/fragment.glsl");
	shaderManager.add_shaderProg("test", shaderNames);

	// Camera stuff
	int w, h;
	SDL_GetWindowSize(_manager->get_window()->get_id(), &w, &h);
	_projection = glm::perspective(_fov, float(w)/h, _nearView, _farView);
	_view = glm::translate(glm::mat4(1.0f), _pos);

	return true;
}

void MainGame::update(float dt)
{
	// SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "MainGame::update() %f", dt);
	// Update the physics. Simulate.
	// Do <current_state> += DT
	// and also <interp_state> = <current_state>
	// _view = glm::translate(glm::mat4(1.0f), _pos);
	_view = glm::rotate(_view, dt*100, _rotV);
	ShaderProg* shaderProg = shaderManager.get_shaderProg("test");
	glUseProgram(shaderProg->get_id());
	GLuint viewID = shaderProg->get_uniform("view");
	glUniformMatrix4fv(viewID, 1, false, glm::value_ptr(_view));
	glUseProgram(0);
}

void MainGame::interp(float dt)
{
	// SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "MainGame::interp() %f", dt);
	// Interpolate the physics. Don't simulate.
	// Do <interp_state> += DT
	glm::mat4 interpView = glm::rotate(_view, dt*100, _rotV);
	ShaderProg* shaderProg = shaderManager.get_shaderProg("test");
	glUseProgram(shaderProg->get_id());
	GLuint viewID = shaderProg->get_uniform("view");
	glUniformMatrix4fv(viewID, 1, false, glm::value_ptr(interpView));
	glUseProgram(0);
}

void MainGame::draw_delete_me()
{
	ShaderProg* shaderProg = shaderManager.get_shaderProg("test");
	glUseProgram(shaderProg->get_id());

	GLuint vboLoc = shaderProg->get_attribute("inVertex");
	GLuint cboLoc = shaderProg->get_attribute("inColor");

	GLuint projectionID = shaderProg->get_uniform("projection");
	GLuint modelID = shaderProg->get_uniform("model");
	glm::mat4 model = glm::mat4(1.0f);
	glUniformMatrix4fv(modelID, 1, false, glm::value_ptr(model));
	glUniformMatrix4fv(projectionID, 1, false, glm::value_ptr(_projection));

	glEnableVertexAttribArray(vboLoc);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo->get_id());
	glVertexAttribPointer(vboLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(cboLoc);
	glBindBuffer(GL_ARRAY_BUFFER, _cbo->get_id());
	glVertexAttribPointer(cboLoc, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	_ibo->draw();

	glDisableVertexAttribArray(vboLoc);
	glDisableVertexAttribArray(cboLoc);
	glUseProgram(0);
}

void jump(Game* game, float dt, bool state, int x, int y)
{
	if (state)
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "jumping: %f", dt);
}

void crouch(Game* game, float dt, bool state, int x, int y)
{
	if (state)
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "crouching: %f", dt);
}

void quit(Game* game, float dt, bool state, int x, int y)
{
	if (state)
		game->get_manager()->quit();
}

void toggle_fullscreen(Game* game, float dt, bool state, int x, int y)
{
	if (state)
		game->get_manager()->get_window()->toggle_fullscreen();
}

void toggle_cursor(Game* game, float dt, bool state, int x, int y)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "toggle_cursor");
	SDL_bool cursorShown = SDL_bool((SDL_ShowCursor(-1) == 1));
	SDL_ShowCursor(!cursorShown);
	SDL_SetRelativeMouseMode(SDL_bool(SDL_ShowCursor(-1) == 0));
	SDL_Window* id = game->get_manager()->get_window()->get_id();
	SDL_SetWindowGrab(id, cursorShown);
}

void toggle_menu(Game* game, float dt, bool state, int x, int y)
{
	if (state)
	{
		SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "toggle_menu");
		toggle_cursor(game, dt, state, x, y);
		string top = game->get_input()->top();
		if (top == "menu")
		{
			game->get_input()->clear();
			game->get_input()->push("main");
		}
		else
		{
			game->get_input()->clear();
			game->get_input()->push("menu");
		}
	}
}

void menu_click(Game* game, float dt, bool state, int x, int y)
{
	if (state)
		SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "UI Clicked (%i,%i)", x, y);
}

void attack(Game* game, float dt, bool state, int x, int y)
{
	if (state)
		SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "Attack Charging!");
	else
		SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "Attack Released!");
}
