#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <SFML/Window.hpp>

class Game;

class Keyboard
{
	public:

		Keyboard(Game* game);

		Game* get_game();

		void key_released(sf::Keyboard::Key key);
		void check_keys(float dt);

	private:

		Keyboard();
		Game* game;
};

#endif /* KEYBOARD_H_ */
