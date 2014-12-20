#include <iostream>
#include <algorithm>

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>

#include "renderer.h"
#include "manager.h"
#include "window.h"

using namespace std;

Renderer::Renderer(Manager* manager): _manager(manager)
{}

Renderer::~Renderer()
{}

Manager* Renderer::get_manager()
{
	return _manager;
}

void Renderer::init_gl()
{
	GLenum glew = glewInit();
	if (glew != GLEW_OK)
	{
		cerr << "GLEW Error: " << glewGetErrorString(glew) << endl;
		_manager->quit();
	}
	// glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// glLineWidth(5.0f);
	// glEnableClientState(GL_VERTEX_ARRAY);
	// glEnableClientState(GL_COLOR_ARRAY);
	// glEnableClientState(GL_INDEX_ARRAY);
	// glEnable(GL_DEPTH_TEST);
	// glEnable(GL_BLEND);
	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(10.0);
}

void Renderer::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.3f, 0.6f, 0.9f);
	glBegin(GL_POINTS);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	_manager->get_window()->display();
}
