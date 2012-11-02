#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
#include "defines.h"
#include "manager.h"
#include "window.h"
#include "game.h"
#include "renderer.h"

Window::Window(Manager* manager, int argc, char** argv,
		string title, uint w, uint h):
	sf::Window(),
	manager(manager), argc(argc), argv(argv),
	w(w), h(h), title(title), isFullScreen(false),
	fullScreenMode(sf::VideoMode::getDesktopMode()),
	framerate(60.0f)
{
	// Make sure this is the order of operations: window, glew, gl
	setFramerateLimit(framerate);
	create_window();
}

Manager* Window::get_manager()
{
	return manager;
}

void Window::init_gl()
{
	get_manager()->get_game()->get_renderer()->init_gl();
}

void Window::init_glew()
{
	GLenum glew = glewInit();
	if (glew != GLEW_OK)
	{
		cerr << "GLEW Error: " << glewGetErrorString(glew) << endl;
		close();
	}
}

void Window::resize(uint width, uint height)
{
	if (!isFullScreen)
	{
		w = width;
		h = height;
	}
	glViewport(0, 0, width, height);
}

void Window::create_window()
{
	if (isFullScreen)
	{
		// TODO: Sometime in the future, let the user choose which resolution.
//		vector<sf::VideoMode> fullScreenModes = sf::VideoMode::getFullscreenModes();
		close();
		create(fullScreenMode, title, sf::Style::Fullscreen);
	}
	else
	{
		close();
		create(sf::VideoMode(w, h), title);
	}
	init_glew();
	init_gl();
}

void Window::toggle_fullscreen()
{
	isFullScreen = !isFullScreen;
	create_window();
}

uint Window::width()
{
	return isFullScreen ? fullScreenMode.width : w;
}

uint Window::height()
{
	return isFullScreen ? fullScreenMode.height : h;
}

float Window::get_framerate() const
{
	return framerate;
}
