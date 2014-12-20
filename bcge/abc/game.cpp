#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "game.h"
#include "../manager.h"
#include "../keyboard.h"

using namespace std;

Game::Game(Manager* manager):
	_manager(manager), _isPaused(false)
{
	_keyboard = new Keyboard(this);
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

void Game::update(float dt)
{
	// Update the physics. Simulate.

	if (!_isPaused)
		cout << dt << " update - running" << endl;
	else
		cout << dt << " update - paused" << endl;
}

void Game::interp(float dt)
{
	// Interpolate the physics. Don't simulate.

	// if (!_isPaused)
	// 		cout << dt << " interp - running" << endl;
	// 	else
	// 		cout << dt << " interp - paused" << endl;
}

void Game::toggle_pause()
{
	_isPaused = !_isPaused;
}
