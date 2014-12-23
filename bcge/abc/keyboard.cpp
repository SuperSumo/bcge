#include <iostream>

#include <gl/glew.h>
#include <SFML/Window.hpp>

#include "keyboard.h"
#include "../abc/game.h"
#include "../manager.h"
#include "../window.h"

using namespace std;

Keyboard::Keyboard(Game* game):
	_game(game)
{
	_keys = new KeyState[sf::Keyboard::KeyCount];
}

Keyboard::~Keyboard()
{
	delete _keys;
}

Game* Keyboard::get_game()
{
	return _game;
}

void Keyboard::key_pressed(sf::Keyboard::Key key)
{
	// _eventQueue->push(Key(key, true));
	_keys[key] = KEY_DOWN;
}

void Keyboard::key_released(sf::Keyboard::Key key)
{
	// _eventQueue->push(Key(key, false));
	_keys[key] = KEY_UP;
}

void Keyboard::_check_keys(float dt)
{
	for (int i=0; i<sf::Keyboard::KeyCount; i++)
		check_key(sf::Keyboard::Key(i), _keys[i], dt);
}
