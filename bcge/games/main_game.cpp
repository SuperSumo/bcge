#include <iostream>
#include <gl/glew.h>
#include <SFML/Graphics.hpp>

#include "../defines_constants_typedefs.h"
#include "../manager.h"
#include "../shaderProg.h"
#include "../shaderManager.h"
#include "main_game.h"
#include "main_keyboard.h"

using namespace std;

MainGame::MainGame(Manager* manager):
	Game(manager),
	_vbo(0), _cbo(0)
{
	cout << "MainGame::MainGame()" << endl;
}

MainGame::~MainGame()
{}

void MainGame::load()
{
	cout << "MainGame::load()" << endl;

	// Load the keyboard for this game
	_keyboard = new MainKeyboard(this);

	// Load the model data. Delete this and move into a game loading thing.
	float verts[3] = {0.0f, 0.0f, 0.0f};
	float colors[3] = {0.3f, 0.6f, 0.9f};
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glGenBuffers(1, &_cbo);
	glBindBuffer(GL_ARRAY_BUFFER, _cbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	shaderManager.reload();
	shaderManager.add_shader(GL_VERTEX_SHADER, "shaders/vertex.glsl");
	shaderManager.add_shader(GL_FRAGMENT_SHADER, "shaders/fragment.glsl");

	StringVec shaderNames;
	shaderNames.push_back("shaders/vertex.glsl");
	shaderNames.push_back("shaders/fragment.glsl");
	shaderManager.add_shaderProg("test", shaderNames);

	// _shaderProg->add_shader(_vShader);
	// _shaderProg->add_shader(_fShader);
	// _shaderProg->compile();
}

void MainGame::update(float dt)
{
	// Update the physics. Simulate.
	// Do <current_state> += DT
	// and also <interp_state> = <current_state>
	// cout << dt << " MainGame::update() " << _isPaused << endl;
}

void MainGame::interp(float dt)
{
	// Interpolate the physics. Don't simulate.
	// Do <interp_state> += DT
	// cout << dt << " MainGame::interp() " << _isPaused << endl;
}

void MainGame::draw()
{
	ShaderProg* shaderProg = shaderManager.get_shaderProg("test");
	glUseProgram(shaderProg->get_id());

	GLuint vboLoc = shaderProg->get_attribute("inVertex");
	GLuint cboLoc = shaderProg->get_attribute("inColor");

	glEnableVertexAttribArray(vboLoc);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glVertexAttribPointer(vboLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(cboLoc);
	glBindBuffer(GL_ARRAY_BUFFER, _cbo);
	glVertexAttribPointer(cboLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_POINTS, 0, 1);

	glDisableVertexAttribArray(vboLoc);
	glDisableVertexAttribArray(cboLoc);
	glUseProgram(0);
}
