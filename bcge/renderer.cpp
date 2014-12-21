#include <gl/glew.h>
#include <SFML/OpenGL.hpp>

#include "renderer.h"
#include "manager.h"
#include "window.h"

using namespace std;

Renderer::Renderer(Manager* manager):
	_manager(manager)
{}

void Renderer::initialize()
{
	glewExperimental = GL_TRUE;
	GLenum glew = glewInit();
	if (glew != GLEW_OK)
	{
		cerr << "GLEW Error: " << glewGetErrorString(glew) << endl;
		_manager->get_window()->close();
	}

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glLineWidth(5.0f);
	glPointSize(10.0f);
	glEnable(GL_DEPTH_TEST);
}

void Renderer::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_manager->draw();

	// Swap the buffers
	_manager->get_window()->display();
}
