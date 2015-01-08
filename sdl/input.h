#ifndef INPUT_H
#define INPUT_H

#include <queue>
#include <map>
#include <string>

#include <SDL2/SDL.h>

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
		return inputID < o.inputID || \
			(inputID == o.inputID && state < o.state);
	}

	string inputID;
	bool state; // True for down, false for up
	int x;
	int y;
};

typedef void (*ActionFuncPtr)(Game*, float, int, int);
typedef map<InputAction, string> InputMap;
typedef queue<InputAction> InputQueue;
typedef map<string, ActionFuncPtr> ActionMap;

class Input
{
	public:

		Input(string section, Game* game);

		void register_callback(string defaultInput, string action,
			ActionFuncPtr funcPtr, bool state=true);
		void enqueue_action(string inputID, bool state=true, int x=0, int y=0);
		void execute_actions(float dt);

	private:

		Input();

		string _section; // The controls subsection
		Game* _game; // Not owned by this class
		InputMap _inputMap;
		InputQueue _inputQueue;
		ActionMap _actionMap;
};

#endif