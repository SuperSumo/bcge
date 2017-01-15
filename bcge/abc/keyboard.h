// TODO: Make this an ABC and create a derived keyboard class for the current
// game. Also, I think I want to make a folder for each game and put the
// derived classes in there.

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <gl/glew.h>
#include <SFML/Window.hpp>

using namespace std;

enum KeyState
{
	KEY_RESET = 0,
	KEY_DOWN = 1,
	KEY_UP = 2
};

class Game;

class Keyboard
{
	public:

		Keyboard(Game* game);
		virtual ~Keyboard();

		Game* get_game();

		void key_pressed(sf::Keyboard::Key key);
		void key_released(sf::Keyboard::Key key);
		void _check_keys(float dt);
		virtual void check_key(sf::Keyboard::Key key, KeyState state, float dt)=0;

	protected:

		Game* _game;
		KeyState* _keys;

	private:

		Keyboard();

};

#endif
