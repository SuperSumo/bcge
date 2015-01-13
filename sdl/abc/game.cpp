#include <SDL2/SDL.h>

#include "game.h"
#include "../input.h"
#include "../manager.h"

using namespace std;

Game::Game(Manager* manager):
	_manager(manager),
	_currentInput(0)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Game::Game()");
}

Game::~Game()
{
	// Delete all the Inputs in the input map
	for (InputMap::iterator i = _inputMap.begin(); i != _inputMap.end(); ++i)
		delete i->second;
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Game::~Game()");
}

Manager* Game::get_manager()
{
	return _manager;
}

void Game::add_input(string name)
{
	if (_inputMap.find(name) != _inputMap.end())
		delete _inputMap[name];
	_inputMap[name] = new Input(name, this);
	_currentInput = _inputMap[name];
}

Input* Game::get_input(string name)
{
	// By default, return the current input
	if (name.length() == 0)
		return _currentInput;

	// Otherwise, return the specified input
	if (_inputMap.find(name) == _inputMap.end())
	{
		cout << "Game::get_input - Input " << name << " not found!" << endl;
		return 0;
	}
	return _inputMap[name];
}
