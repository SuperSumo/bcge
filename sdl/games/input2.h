#ifndef INPUT2_H
#define INPUT2_H

#include <iostream>
#include <string>
#include <map>
#include <queue>

#include "../defines_constants_typedefs.h"
#include "../abc/game.h"

using namespace std;

struct UserInput
{
	// The key for keyboard and mouse_*, gamepad_*. For mouse and keyboard, I
	// will need to translate the numberical ID got from SDL into a string. For
	// the keyboard, use SDL_GetKeyName(event->key.keysym.sym);
	string inputID;
	bool state; // true for press, false for release
	int x; // For mouse clicks, relative to window
	int y; // For mouse clicks, relative to window
};

typedef void (*ActionFuncPtr)(Game*, float, int, int);
typedef map<string, ActionFuncPtr> ActionMap;
typedef map<UserInput, string> InputMap;
typedef queue<UserInput> InputQueue;

class Input2
{
	public:

		Input2(Game* game);

		void register_callback(string actionName, ActionFuncPtr funcPtr,
			string defaultInputID, bool state);
		void add_input_event(UserInput userInput);
		void execute(float dt); // Run all queued actions

	protected:

		void _execute_action(string actionName, float dt, int x, int y);

		Game* _game;

	private:

		Input2();

		ActionMap _actionMap;	// The action_name->ActionFuncPtr map
		InputMap _inputMap;		// The UserInput->action_name map
		InputQueue _inputQueue;	// The queue of UserInput to execute
};

class InputGame: public Game
{
	public:

		InputGame(Manager* manager);
		virtual ~InputGame();

		virtual bool init();
		virtual void update(float dt);
		virtual void interp(float dt);

		// TODO: Remove this method
		virtual void draw_delete_me();

	private:

		InputGame();

};

// These are defined outside of a class, so I can pass around function
// pointers easily.
void action_1(Game* game, float dt, int x, int y);
void action_2(Game* game, float dt, int x, int y);
void action_3(Game* game, float dt, int x, int y);

#endif
