#include <iostream>
#include <gl/glew.h>
#include <SFML/Graphics.hpp>

#include "main_game.h"
#include "main_keyboard.h"
#include "../manager.h"

using namespace std;

MainGame::MainGame(Manager* manager):
	Game(manager),
	_vbo(0), _cbo(0), _shaderProgID(0),
	_vShader(0),
	_fShader(0)
{
	cout << "MainGame::MainGame()" << endl;
}

MainGame::~MainGame()
{
	delete _vShader;
	delete _fShader;
}

void MainGame::load()
{
	cout << "MainGame::load()" << endl;

	// Load the keyboard for this game
	_keyboard = new MainKeyboard(this);

	// TODO: MOVE ALL THIS CODE OUT OF HERE
	if (_vShader)
		delete _vShader;
	if (_fShader)
		delete _fShader;
	_vShader = new Shader(GL_VERTEX_SHADER);
	_fShader = new Shader(GL_FRAGMENT_SHADER);

	// Load the model data. Delete this and move into a game loading thing.
	float verts[3] = {0.0f, 0.0f, 0.0f};
	float colors[3] = {0.3f, 0.6f, 0.9f};
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glGenBuffers(1, &_cbo);
	glBindBuffer(GL_ARRAY_BUFFER, _cbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	// // TODO: I need to finish the shader manager first.
	// //	_shaderManager->add_shader("vertex.glsl");
	_vShader->load("shaders/vertex.glsl"); // Relative to main.cpp
	_fShader->load("shaders/fragment.glsl"); // Relative to main.cpp

	_shaderProgID = glCreateProgram();
	glAttachShader(_shaderProgID, _vShader->get_id());
	glAttachShader(_shaderProgID, _fShader->get_id());
	glLinkProgram(_shaderProgID);
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
	// glColor3f(0.3f, 0.6f, 0.9f);
	// glBegin(GL_POINTS);
	// glVertex3f(0.0f, 0.0f, 0.0f);
	// glEnd();

	glUseProgram(_shaderProgID);

	GLuint vboLoc = glGetAttribLocation(_shaderProgID, "inVertex");
	GLuint cboLoc = glGetAttribLocation(_shaderProgID, "inColor");

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
