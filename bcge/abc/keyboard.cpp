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
	// _eventQueue = &_keyQueues[_queueIndex];
	// _keyQueue = &_keyQueues[1 - _queueIndex];
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
	// Loop through the key queue and call check_key for each key in the queue.
	// while(!_eventQueue->empty())
	// {
	// 	check_key(_eventQueue->front(), dt);
	// 	_eventQueue->pop();
	// }
	// _keyQueue = &_keyQueues[_queueIndex]; // Use this in check_key
	// _queueIndex = 1 - _queueIndex;
	// _eventQueue = &_keyQueues[_queueIndex]; // Use this in events

	for (int i=0; i<sf::Keyboard::KeyCount; i++)
		check_key(sf::Keyboard::Key(i), _keys[i], dt);
}

// void Keyboard::check_key(Key key, float dt)
void Keyboard::check_key(sf::Keyboard::Key key, KeyState state, float dt)
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
			{
				cout << "w is up" << endl;
				_keys[key] = KEY_RESET;
			}
			break;

		default:
			break;
	}
}

// TODO: I *DO* need to make a flip/flop queue because of re-adding the keys
// to the queue. If I re-add them to the current queue I will have an
// infinite loop because of the while loop;
