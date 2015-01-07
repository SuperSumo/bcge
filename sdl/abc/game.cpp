#include <SDL2/SDL.h>

#include "game.h"
#include "input.h"
#include "../games/input2.h"
#include "../manager.h"

using namespace std;

Game::Game(Manager* manager):
	_manager(manager),
	_input(0), _input2(0)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Game::Game()");
}

Game::~Game()
{
	delete _input;
	delete _input2;
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Game::~Game()");
}

bool Game::_init()
{
	bool allGood = _input->init();
	return allGood & init();
}

Manager* Game::get_manager()
{
	return _manager;
}

Input* Game::get_input()
{
	return _input;
}

Input2* Game::get_input2()
{
	return _input2;
}
