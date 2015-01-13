#include <string>

#include <SDL2/SDL.h>
#include <jsoncpp/json/json.h>

#include "input.h"
#include "abc/game.h"
#include "manager.h"

using namespace std;

Input::Input(string section, Game* game):
	_section(section), _game(game)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "Input::Input()");
}

void Input::add_action(string defaultInput, string action, ActionFuncPtr funcPtr,
	bool state)
{
	// Get the input from the config file
	Json::Value val = _game->get_manager()->config.root["controls"][_section];
	string input = val.get(action, defaultInput).asString();

	// If it wasn't initially set, set it now
	_game->get_manager()->config.root["controls"][_section][action] = input;

	// Make the InputAction structure and add to the _inputActionMap
	_inputActionMap[InputAction(input, state)] = action;

	// Map the action name to the function pointer
	_actionFuncPtrMap[action] = funcPtr;

	SDL_LogInfo(SDL_LOG_CATEGORY_INPUT,
		"Input::add_action() - Mapped %s as %s %s",
		action.c_str(), input.c_str(), (state ? "down" : "up"));
}

void Input::enqueue_action(string inputID, bool state, int x, int y)
{
	// Create an InputAction object
	InputAction inputAction(inputID, state, x, y);

	// Ensure inputAction is a key in _inputActionMap
	if (_inputActionMap.find(inputAction) == _inputActionMap.end())
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_INPUT,
		"Input::enqueue_action() - InputAction %s %s not mapped",
		inputID.c_str(), (state ? "down" : "up"));
		return;
	}

	// Add to the queue
	_inputActionQueue.push(inputAction);
}

void Input::execute_actions(float dt)
{
	InputAction inputAction;
	while (!_inputActionQueue.empty())
	{
		// Grab the next action from the queue
		inputAction = _inputActionQueue.front();

		SDL_LogInfo(SDL_LOG_CATEGORY_INPUT,
		"Input::execute_actions() - Calling %s %s",
		inputAction.inputID.c_str(), (inputAction.state ? "down" : "up"));

		// Ensure inputAction is a key in _inputActionMap
		if (_inputActionMap.find(inputAction) == _inputActionMap.end())
		{
			SDL_LogWarn(SDL_LOG_CATEGORY_INPUT,
			"Input::execute_actions() - InputAction %s %s not mapped",
			inputAction.inputID.c_str(), (inputAction.state ? "down" : "up"));
			_inputActionQueue.pop();
			continue;
		}

		// Get the action name from the inputAction
		string actionName = _inputActionMap[inputAction];

		// Ensure actionName is a key in _actionFuncPtrMap
		if (_actionFuncPtrMap.find(actionName) == _actionFuncPtrMap.end())
		{
			SDL_LogWarn(SDL_LOG_CATEGORY_INPUT,
			"Input::execute_actions() - Action %s not mapped",
			actionName.c_str());
			_inputActionQueue.pop();
			continue;
		}

		// Call the specific function pointer
		_actionFuncPtrMap[actionName](_game, dt, inputAction.x, inputAction.y);

		// Remove the action from the queue
		_inputActionQueue.pop();
	}
}
