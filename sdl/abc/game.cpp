#include <SDL2/SDL.h>

#include "game.h"
#include "../input.h"
#include "../manager.h"

using namespace std;

Game::Game(Manager* manager):
	_manager(manager),
	_input(0)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Game::Game()");
}

Game::~Game()
{
	// Delete the input manager
	delete _input;
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Game::~Game()");
}

Manager* Game::get_manager()
{
	return _manager;
}

Input* Game::get_input(string name)
{
	return _input;
}
