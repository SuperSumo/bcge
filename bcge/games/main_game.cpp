#include <iostream>
#include <gl/glew.h>
#include <SFML/Graphics.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../defines_constants_typedefs.h"
#include "../manager.h"
#include "../shaderProg.h"
#include "../shaderManager.h"
#include "../window.h"
#include "main_game.h"
#include "main_keyboard.h"

using namespace std;

MainGame::MainGame(Manager* manager):
	Game(manager), _fov(45.0f), _nearView(0.1f), _farView(100.0f),
	_rotV(glm::vec3(2,3,1)), _pos(glm::vec3(0,0,-4))
{
	cout << "MainGame::MainGame()" << endl;
	_vbo = new Buffer(VBO, GL_FLOAT);
	_cbo = new Buffer(CBO, GL_FLOAT);
	_ibo = new Buffer(IBO, GL_UNSIGNED_INT);

	// Load the keyboard for this game
	_keyboard = new MainKeyboard(this);
}

MainGame::~MainGame()
{
	delete _vbo;
	delete _cbo;
	delete _ibo;
}

void MainGame::load()
{
	cout << "MainGame::load()" << endl;

	// Load the model data. Delete this and move into a game loading thing.

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

	cout << "BUFFERS LOADED? " << allGood << endl;
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
	uint w = _manager->get_window()->width();
	uint h = _manager->get_window()->height();

	_projection = glm::perspective(_fov, float(w)/h, _nearView, _farView);
	_view = glm::translate(glm::mat4(1.0f), _pos);

	cout << "width: " << w << "\nheight: " << h << endl;
	_projection = glm::perspective(_fov, float(w)/h, _nearView, _farView);
	_view = glm::translate(glm::mat4(1.0f), _pos);
}

void MainGame::update(float dt)
{
	// Update the physics. Simulate.
	// Do <current_state> += DT
	// and also <interp_state> = <current_state>
	cout << dt << " MainGame::update() " << _isPaused << endl;
	// _view = glm::translate(glm::mat4(1.0f), _pos);
	_view = glm::rotate(_view, dt, _rotV);
	ShaderProg* shaderProg = shaderManager.get_shaderProg("test");
	glUseProgram(shaderProg->get_id());
	GLuint viewID = shaderProg->get_uniform("view");
	glUniformMatrix4fv(viewID, 1, false, glm::value_ptr(_view));
	glUseProgram(0);
}

void MainGame::interp(float dt)
{
	// Interpolate the physics. Don't simulate.
	// Do <interp_state> += DT
	glm::mat4 interpView = glm::rotate(_view, dt, _rotV);
	ShaderProg* shaderProg = shaderManager.get_shaderProg("test");
	glUseProgram(shaderProg->get_id());
	GLuint viewID = shaderProg->get_uniform("view");
	glUniformMatrix4fv(viewID, 1, false, glm::value_ptr(interpView));
	glUseProgram(0);
	cout << dt << " MainGame::interp() " << _isPaused << endl;
}

void MainGame::draw()
{
	ShaderProg* shaderProg = shaderManager.get_shaderProg("test");
	glUseProgram(shaderProg->get_id());

	GLuint vboLoc = shaderProg->get_attribute("inVertex");
	GLuint cboLoc = shaderProg->get_attribute("inColor");

	// GLuint viewID = shaderProg->get_uniform("view");
	GLuint projectionID = shaderProg->get_uniform("projection");
	GLuint modelID = shaderProg->get_uniform("model");
	glm::mat4 model = glm::mat4(1.0f);
	glUniformMatrix4fv(modelID, 1, false, glm::value_ptr(model));
	// glUniformMatrix4fv(viewID, 1, false, glm::value_ptr(_view));
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
	// _vbo->draw();
	// glDrawArrays(GL_POINTS, 0, 1);

	glDisableVertexAttribArray(vboLoc);
	glDisableVertexAttribArray(cboLoc);
	glUseProgram(0);
}
