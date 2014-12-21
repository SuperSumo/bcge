#include <iostream>

#include <gl/glew.h>
#include <SFML/Window.hpp>

#include "keyboard.h"
#include "abc/game.h"
#include "renderer.h"
#include "manager.h"
#include "window.h"
// #include "camera.h"

using namespace std;

Keyboard::Keyboard(Game* game): _game(game)
{
	_keyMask = new bool[sf::Keyboard::KeyCount];
}

Keyboard::~Keyboard()
{
	delete[] _keyMask;
}

Game* Keyboard::get_game()
{
	return _game;
}

void Keyboard::key_pressed(sf::Keyboard::Key key)
{
	cout << "a key was pressed: " << key << endl;
	cout << "number of keys: " << sf::Keyboard::KeyCount << endl;
	_keyMask[key] = true;
}

void Keyboard::key_released(sf::Keyboard::Key key)
{
	// A single key click checker
	switch (key)
	{
		case sf::Keyboard::Escape:
		case sf::Keyboard::Q:
			get_game()->get_manager()->get_window()->close();
			break;
		case sf::Keyboard::F:
			get_game()->get_manager()->get_window()->toggle_fullscreen();
			break;
		case sf::Keyboard::P:
			get_game()->toggle_pause();
			break;
		default:
			break;
	}
}

bool Keyboard::isKeyDown(sf::Keyboard::Key key)
{
	return _keyMask[key];
}

void Keyboard::check_keys(float dt)
{
	// Loop through the key queue and call key_action(<key, state>, dt) for
	// each <key, state> pair in the queue.
}

// On key_pressed event, add a [key/<down>] pair to a FIFO queue.
// On key_released event, add a [key/<up>] pair to a FIFO queue.
// In _check_keys, create a loop until the queue is empty. In the loop call
// key_action for each item in the queue. Create a virtual method key_action
// which takes a (pair<key,state>, dt) and override that method in each derived
// keyboard class.
