#ifndef MAIN_KEYBOARD_H
#define MAIN_KEYBOARD_H

#include "../abc/keyboard.h"

class MainKeyboard: public Keyboard
{
	public:

		MainKeyboard(Game* game);

		virtual void check_key(sf::Keyboard::Key key, KeyState state, float dt);

	private:

		MainKeyboard();

};

#endif
