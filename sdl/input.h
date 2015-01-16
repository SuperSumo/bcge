#ifndef INPUT_H
#define INPUT_H

#include <queue>
#include <map>
#include <string>

#include <SDL2/SDL.h>

#include "named_stack.h"

using namespace std;

class Game;

struct InputAction
{
	InputAction(){};
	InputAction(string inputID, bool state=true, int x=0, int y=0):
		inputID(inputID), state(state), x(x), y(y)
	{}

	// This is so I can use this class as a key in a std::map
	bool operator<(const InputAction& o) const
	{
		return inputID < o.inputID;
	}

	string inputID;
	bool state; // True for down, false for up
	int x;
	int y;
};

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

#endif
