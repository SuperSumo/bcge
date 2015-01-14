#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <string>
#include <map>
#include <queue>

#include "config.h"
#include "named_stack.h"

using namespace std;

struct InputAction
{
	InputAction(){};
	InputAction(string inputID, bool state=true, int x=0, int y=0):
		inputID(inputID), state(state), x(x), y(y)
	{}

	// This is so I can use this class as a key in a std::map
	bool operator<(const InputAction& o) const
	{
		return inputID < o.inputID || \
			(inputID == o.inputID && state < o.state);
	}

    string inputID;
    bool state; // True for down, false for up
	int x;
	int y;
};

class Game;

typedef void (*ActionFuncPtr)(Game*, float, bool, int, int);
typedef map<InputAction, string> InputActionMap;
typedef queue<InputAction> InputActionQueue;
typedef map<string, ActionFuncPtr> ActionFuncPtrMap;

class Input: public NamedStack<InputActionMap>
{
    public:

		Input(Game* game);

		bool init(); // Load the key bindings from the json file
		void register_callback(string action, ActionFuncPtr funcPtr);

		void enqueue_action(string inputID, bool state=true, int x=0, int y=0);
		void execute_actions(float dt);

	private:

		Input();

		Game* _game; // Not owned by this class
		InputActionQueue _inputActionQueue;
        ActionFuncPtrMap _actionFuncPtrMap;
};

typedef map<string, Input*> InputMap;

class Game
{
	public:

		Game();
		virtual ~Game();
		void init();

		Input* get_input(string name=string());

		Config config;

	private:

		Input* _input;
};

void jump(Game* game, float dt, bool state, int x, int y);
void attack(Game* game, float dt, bool state, int x, int y);
void crouch(Game* game, float dt, bool state, int x, int y);
void quit(Game* game, float dt, bool state, int x, int y);
void toggle_cursor(Game* game, float dt, bool state, int x, int y);

#endif
