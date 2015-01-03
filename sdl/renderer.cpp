#include <iostream>

#include <gl/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "renderer.h"
#include "manager.h"
#include "window.h"
#include "abc/game.h"

using namespace std;

Renderer::Renderer(Manager* manager):
	_manager(manager)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Renderer::Renderer()");

	// Set some SDL GL attributes in the constructor, before calling init.
	// I need the order to be:
	// 1. set attributes	Renderer()
	// 2. create window		Window(); window->init()
	// 3. create context	renderer->init()
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

Renderer::~Renderer()
{
	SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Renderer::~Renderer()");
}

bool Renderer::init()
{
	SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Renderer::init()");

	// Create the SDL OpenGL context
	_context = SDL_GL_CreateContext(_manager->get_window()->get_id());
	if(_context == NULL)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_RENDER,
			"Renderer::init() - Could not create OpenGL context: %s\n",
			SDL_GetError());
		return false;
	}

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum glew = glewInit();
	if (glew != GLEW_OK)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_RENDER,
			"Renderer::init() - GLEW Error: %s\n",
			glewGetErrorString(glew));
		return false;
	}

	// Print out some OpenGL version info
	SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "OpenGL Version: %s\n",
		glGetString(GL_VERSION));
	SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "OpenGL Vendor: %s\n",
		glGetString(GL_VENDOR));
	SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "OpenGL Video Card: %s\n",
		glGetString(GL_RENDERER));
	SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "OpenGL Shading: %s\n",
		glGetString(GL_SHADING_LANGUAGE_VERSION));

	// Misc OpenGL settings which will change later.
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_CULL_FACE);
	// glCullFace(GL_BACK);
	// glLineWidth(5.0f);
	// glPointSize(10.0f);
	// glEnable(GL_DEPTH_TEST); // I need this line for things to work

	return true;
}

void Renderer::render(Game* game)
{
	// SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Renderer::render()");
	// Iterate through the objects in the game to get their states and render
	// them according to their associated Object. I might want to make an
	// ObjectManager which keeps track of objects and their instances.

	// For now, just call the game's draw call, but I want to move the opengl
	// calls into the renderer and not keep them in the game.
	game->draw_delete_me();

	// Update screen
	SDL_GL_SwapWindow(_manager->get_window()->get_id());
}

void Renderer::set_viewport(uint x, uint y, uint width, uint height)
{
	glViewport(x, y, width, height);
}
