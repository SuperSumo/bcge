#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <queue>

#include <SDL2/SDL.h>

#include "input2.h"
#include "../abc/game.h"
#include "../manager.h"

using namespace std;

Input2::Input2(Game* game):_game(game)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "Input2::Input2()");
}

void Input2::register_callback(string actionName, ActionFuncPtr funcPtr,
	string defaultInputID, bool state)
{
	// Create the input name based on the defaultInput
	// TODO: Just add these prefixes during the event dispatching in the manager!!
	// stringstream inputName;
	// switch (defaultInput.inputType)
	// {
	// 	case KEYBOARD_INPUT:
	// 		inputName << defaultInput.inputID;
	// 		break;

	// 	case MOUSE_INPUT:
	// 		inputName << "mouse_" << defaultInput.inputID;
	// 		break;

	// 	case GAMEPAD_INPUT:
	// 		inputName << "gamepad_" << defaultInput.inputID;
	// 		break;

	// 	default:
	// 		break;
	// }

	// Get the key from the config file
	string inputNameFromConfig = _game->get_manager()->\
		config.root.get(actionName, defaultInputID).asString();

	// Set the key again. If the key wasn't initially set, it is now.
	_game->get_manager()->config.root[actionName] = inputNameFromConfig;

	// Add keymap with a UserInput struct
	SDL_LogInfo(SDL_LOG_CATEGORY_INPUT,
		"Input::_add_action() - Added %s as %s",
		inputNameFromConfig.c_str(), actionName.c_str());
	UserInput input = {inputNameFromConfig, state, 0, 0};
	_inputMap[input] = actionName;

	// Add the function pointer to the map with the action name as the key
	_actionMap[actionName] = funcPtr;
}

void Input2::add_input_event(UserInput userInput)
{
	_inputQueue.push(userInput);
}

void Input2::execute(float dt)
{
	// Run all queued actions
	UserInput input;
	while (!_inputQueue.empty())
	{
		input = _inputQueue.front();

		// If the key isn't in the map pop it and go to the next one
		if (_inputMap.find(input) == _inputMap.end())
		{
			_inputQueue.pop();
			continue;
		}

		// If it is, save it
		string actionName = _inputMap[input];

		// Call the derived class' execute method
		_execute_action(actionName, dt, input.x, input.y);
		_inputQueue.pop();
	}
}

void Input2::_execute_action(string actionName, float dt, int x, int y)
{
	// Check if the mapping has a function
	if (_actionMap.find(actionName) == _actionMap.end())
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_INPUT, "Action %s has no function",
			actionName.c_str());
		return;
	}

	// Execute the mapped method
	(_actionMap[actionName])(_game, dt, x, y);
}

InputGame::InputGame(Manager* manager):Game(manager)
{}
InputGame::~InputGame()
{}
bool InputGame::init()
{
	_input2->register_callback("jump", action_1, "Q", true);
}
void InputGame::update(float dt)
{}
void InputGame::interp(float dt)
{}
void InputGame::draw_delete_me()
{}

// These are defined outside of a class, so I can pass around function
// pointers easily.
void action_1(Game* game, float dt, int x, int y)
{
	cout << "action 1: " << dt << endl;
}
void action_2(Game* game, float dt, int x, int y)
{
	cout << "action 2: " << dt << endl;
}
void action_3(Game* game, float dt, int x, int y)
{
	cout << "action 3: " << dt << endl;
}
