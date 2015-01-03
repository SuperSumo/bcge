#ifndef MAIN_KEYBOARD_H
#define MAIN_KEYBOARD_H

#include <SDL2/SDL.h>

#include "../abc/input.h"

class MainInput: public Input
{
	public:

		MainInput(Game* game);
		virtual bool init();

	private:

		MainInput();
		virtual void _execute_action(string action, float dt);

		typedef map<string, void (MainInput::*)(float)> ActionMap;
		ActionMap _actionMap;

		// Action methods
		void _quit(float dt);
		void _toggle_fullscreen(float dt);
		void _toggle_cursor(float dt);
		void _mouse_clicked(float dt);
};

#endif
