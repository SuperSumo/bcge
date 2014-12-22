// TODO: Make this an ABC and create a derived keyboard class for the current
// game. Also, I think I want to make a folder for each game and put the
// derived classes in there.

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <gl/glew.h>
#include <SFML/Window.hpp>

class Game;

class Keyboard
{
	public:

		Keyboard(Game* game);
		virtual ~Keyboard();

		Game* get_game();

		void key_pressed(sf::Keyboard::Key key);
		void key_released(sf::Keyboard::Key key);
		bool isKeyDown(sf::Keyboard::Key key);
		void check_keys(float dt);

	private:

		Keyboard();

		Game* _game;
		bool* _keyMask;
};

#endif
