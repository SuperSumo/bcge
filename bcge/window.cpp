#include <iostream>

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "manager.h"
#include "window.h"
#include "renderer.h"

using namespace std;

Window::Window(Manager* manager, string title, uint w, uint h):
	sf::Window(), _manager(manager), _width(w), _height(h), _title(title),
	_isFullScreen(false)
{
	// Make sure this is the order of operations: window, glew, gl
	// TODO: Set this to the user's refresh rate or primus gives errors
	setFramerateLimit(60.0f);
	create_window();
}

Manager* Window::get_manager()
{
	return _manager;
}

void Window::resize(uint width, uint height)
{
	if (!_isFullScreen)
	{
		_width = width;
		_height = height;
	}
	glViewport(0, 0, _width, _height);
}

void Window::create_window()
{
	close();
	if (_isFullScreen)
		create(sf::VideoMode::getDesktopMode(), _title, sf::Style::Fullscreen);
	else
		create(sf::VideoMode(_width, _height), _title);

	// I don't want repeating keys enabled while gaming. Maybe when a user is
	// typing I can turn this on again.
	setKeyRepeatEnabled(false);

	// Window Options - TODO: Load from a config file.
	setVerticalSyncEnabled(true);

	// Since the window was closed we need to re-initilize opengl and reload
	// all the game stuff
	_manager->get_renderer()->init_gl();

	// TODO: Write a method to reload the shaders. I'm not sure where it will
	// go yet.
	// _manager->get_renderer()->get_shader_manager()->reload()
}

void Window::toggle_fullscreen()
{
	_isFullScreen = !_isFullScreen;
	create_window();
}
