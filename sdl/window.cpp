#include <string>
#include <fstream>
#include <sstream>

#include <SDL2/SDL.h>
#include <json/json.h>

#include "manager.h"
#include "window.h"
#include "config.h"

using namespace std;

Window::Window(Manager* manager, uint x, uint y, uint width, uint height):
	_manager(manager), _id(0), _x(x), _y(y), _width(width), _height(height),
	_isFullScreen(false)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Window::Window()");

	// Get the values from the json file if they exist
	_x = _manager->config.root.get("windowX", _x).asUInt();
	_y = _manager->config.root.get("windowY", _y).asUInt();
	_width = _manager->config.root.get("windowWidth", _width).asUInt();
	_height = _manager->config.root.get("windowHeight", _height).asUInt();
	_isFullScreen = _manager->config.root.get("isFullScreen", _isFullScreen).asBool();
}

Window::~Window()
{
	SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Window::~Window()");

	// Update the config file with the latest window dimensions
	int x, y, width, height;
	SDL_GetWindowSize(_id, &width, &height);
	SDL_GetWindowPosition(_id, &x, &y);
	_manager->config.root["windowX"] = x;
	_manager->config.root["windowY"] = y;
	_manager->config.root["windowWidth"] = width;
	_manager->config.root["windowHeight"] = height;
	_manager->config.root["isFullScreen"] = _isFullScreen;

	// Destroy the SDL window
	SDL_DestroyWindow(_id);
	_id = NULL;
}

SDL_Window* Window::get_id() const
{
	return _id;
}

bool Window::create_window()
{
	SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO,
		"Window::create_window() Fullscreen? %i\n", _isFullScreen);

	// If we already have a window, destroy it
	if (_id != NULL)
		SDL_DestroyWindow(_id);

	Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
	flags |= SDL_WINDOW_INPUT_GRABBED; // The mouse can't escape!

	// Check if we are fullscreen
	// TODO: Later on I want to have users select a resolution. The current
	// flag will do native desktop resolution, which might be too taxing for a
	// user's videocard. If I want to change the resolution, use the flag
	// WINDOW_FULLSCREEN_DESKTOP instead with a different SDL_DisplayMode
	// and SDL_SetWindowDisplayMode.
	if (_isFullScreen)
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

	// Create the SDL window
	_id = SDL_CreateWindow(TITLE, _x, _y, _width, _height, flags);

	// If we failed log a message
	if(_id == NULL)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO,
			"Window could not be created: %s\n", SDL_GetError());
		return false;
	}

	// Success
	return true;
}

void Window::toggle_fullscreen()
{
	_isFullScreen = !_isFullScreen;
	int flags = _isFullScreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0;
	SDL_SetWindowFullscreen(_id, flags);
}
