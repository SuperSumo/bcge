#include <iostream>

#include <gl/glew.h>
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
	cout << "Window::Window()" << endl;
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
	cout << "Window::create_window() Fullscreen? " << _isFullScreen << endl;
	close();
	if (_isFullScreen)
		create(sf::VideoMode::getDesktopMode(), _title, sf::Style::Fullscreen);
	else
		create(sf::VideoMode(_width, _height), _title);

	// I don't want repeating keys enabled while gaming. Maybe when a user is
	// typing I can turn this on again.
	setKeyRepeatEnabled(false);

	// Reload the manager since a new OpenGL context was created.
	_manager->reload();
}

void Window::toggle_fullscreen()
{
	_isFullScreen = !_isFullScreen;
	create_window();
}
