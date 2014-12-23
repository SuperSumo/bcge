#include <iostream>

#include "main_keyboard.h"
#include "../abc/game.h"
#include "../manager.h"
#include "../window.h"

using namespace std;

MainKeyboard::MainKeyboard(Game* game):
	Keyboard(game)
{
	cout << "MainKeyboard::MainKeyboard()" << endl;
}

void MainKeyboard::check_key(sf::Keyboard::Key key, KeyState state, float dt)
{
	switch (key)
	{
		case sf::Keyboard::Escape:
		case sf::Keyboard::Q:
			if (state == KEY_UP)
				get_game()->get_manager()->quit();
			break;

		case sf::Keyboard::F:
			if (state == KEY_UP)
				get_game()->get_manager()->get_window()->toggle_fullscreen();
			break;

		case sf::Keyboard::P:
			if (state == KEY_UP)
				get_game()->toggle_pause();
			break;

		case sf::Keyboard::W:
			if (state == KEY_DOWN)
				cout << "w is down" << endl;
			else if (state == KEY_UP)
				cout << "w is up" << endl;
			break;

		default:
			break;
	}
	if (state == KEY_UP)
		_keys[key] = KEY_RESET;
}
