#ifndef INPUT_H
#define INPUT_H

#include <queue>
#include <utility>
#include <map>
#include <string>

#include <SDL2/SDL.h>

using namespace std;

typedef pair<SDL_Scancode, bool> KeyState;
typedef queue<KeyState> KeyQueue;
typedef map<KeyState, string> KeyMap;

typedef pair<Uint8, bool> ButtonState;
typedef queue<ButtonState> ButtonQueue;
typedef map<ButtonState, string> ButtonMap;

class Game;

class Input
{
	public:

		Input(Game* game);
		virtual bool init()=0;

		void key_event(SDL_Scancode key, bool state);
		void button_event(Uint8 button, bool state);
		void _check_input(float dt);

		Game* get_game();

	protected:

		void _add_key_action(string action, SDL_Scancode defaultKey,
			bool state);
		void _add_button_action(string action, Uint8 defaultButton,
			bool state);
		virtual void _execute_action(string action, float dt)=0;

		Game* _game;

	private:

		Input();

		void _check_key(SDL_Scancode key, bool state, float dt);
		void _check_button(Uint8 button, bool state, float dt);

		KeyQueue _keyQueue;
		KeyMap _keyMap;
		ButtonQueue _buttonQueue;
		ButtonMap _buttonMap;
};

#endif
