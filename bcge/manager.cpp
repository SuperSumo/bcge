#include "manager.h"
#include "game.h"
#include "window.h"
#include "renderer.h"
#include <iostream>
using namespace std;

Manager::Manager(int argc, char** argv, Game* initialGame)
{
	set_game(initialGame ? initialGame : new Game(this));
	window = new Window(this, argc, argv);
}

Manager::~Manager()
{
	delete game;
	delete window;
}

void Manager::set_game(Game* gameToSet)
{
	game = gameToSet;
}

Game* Manager::get_game()
{
	return game;
}

Window* Manager::get_window()
{
	return window;
}
