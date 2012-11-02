#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include "renderer.h"
#include "game.h"
#include "defines.h"
#include "manager.h"
#include "window.h"
#include "instance.h"
#include "shader.h"
#include "shaderProg.h"
#include <iostream>
#include <algorithm>
using namespace std;

Renderer::Renderer(Game* game): game(game), progID(-1)
{}

Renderer::~Renderer()
{}

Game* Renderer::get_game()
{
	return game;
}

void Renderer::init_gl()
{
	glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glLineWidth(5.0f);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_INDEX_ARRAY);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::render(vector<Instance*> instances)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(progID);
	vector<Instance*>::iterator i;
	for (i=instances.begin(); i!=instances.end(); i++)
		(*i)->draw();
	glUseProgram(0);
}
