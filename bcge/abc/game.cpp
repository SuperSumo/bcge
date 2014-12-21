#include <iostream>

#include "game.h"
#include "../manager.h"
#include "../keyboard.h"

using namespace std;

Game::Game(Manager* manager):
	_manager(manager), _isPaused(false)
{
	cout << "Game::Game()" << endl;
	_keyboard = new Keyboard(this);
	load();
}

Game::~Game()
{
	delete _keyboard;
}

Manager* Game::get_manager()
{
	return _manager;
}

Keyboard* Game::get_keyboard()
{
	return _keyboard;
}

void Game::toggle_pause()
{
	_isPaused = !_isPaused;
}

void Game::load()
{}
