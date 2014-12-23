// TODO: Make this an ABC and create a derived keyboard class for the current
// game. Also, I think I want to make a folder for each game and put the
// derived classes in there.

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <queue>
#include <utility>

#include <gl/glew.h>
#include <SFML/Window.hpp>

using namespace std;

enum KeyState
{
	KEY_RESET = 0,
	KEY_DOWN = 1,
	KEY_UP = 2
};

// struct Key
// {
// 	Key(sf::Keyboard::Key code, KeyState state): code(code), state(state) {}
// 	sf::Keyboard::Key code;
// 	KeyState state;
// };

// typedef queue<Key> KeyQueue;

class Game;

class Keyboard
{
	public:

		Keyboard(Game* game);
		~Keyboard();

		Game* get_game();

		void key_pressed(sf::Keyboard::Key key);
		void key_released(sf::Keyboard::Key key);
		void _check_keys(float dt);
		virtual void check_key(sf::Keyboard::Key key, KeyState state, float dt);

	protected:

		Game* _game;
		KeyState* _keys;
		// KeyQueue _keyQueues[2];
		// size_t _queueIndex;
		// KeyQueue* _eventQueue;
		// KeyQueue* _keyQueue;

	private:

		Keyboard();

};

#endif
