#include <string>
#include <map>
#include <queue>

#include <SDL2/SDL.h>
#include <jsoncpp/json/json.h>

#include "defines_constants_typedefs.h"
#include "input.h"
#include "named_stack.h"
#include "abc/game.h"
#include "manager.h"

using namespace std;

Input::Input(Game* game):
	_game(game)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "Input::Input()");
}

bool Input::init()
{
	SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "MainGame::init()");

	// Get the controls section
	Json::Value controls = _game->get_manager()->config.root["controls"];

	// Loop through each of the children
	Json::Value::Members sections = controls.getMemberNames();
	InputActionMap* sectionMap;
	string sectionName;
	Json::Value::Members actions;
	string actionName;
	string inputID;
	for (Json::Value::Members::iterator i = sections.begin(); i != sections.end(); ++i)
	{
		// Grab the section name
		sectionName = *i;
		SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "Input::init() - Loading section %s", sectionName.c_str());

		// If the section doesn't exist in the input map, add it
		if (!exists(sectionName))
			add(sectionName);

		// Set the section
		sectionMap = get(sectionName);

		// Loop through the section and add key bindings
		actions = controls[sectionName].getMemberNames();
		for (Json::Value::Members::iterator j = actions.begin(); j != actions.end(); ++j)
		{
			// Grab the action name
			actionName = *j;

			// Ensure actionName is a key in _actionFuncPtrMap
			if (_actionFuncPtrMap.find(actionName) == _actionFuncPtrMap.end())
			{
				SDL_LogWarn(SDL_LOG_CATEGORY_INPUT, "Input::init() - Action %s not mapped to a function", actionName.c_str());
				continue;
			}

			// Add the action binding to the map
			inputID = controls[sectionName][actionName].asString();
			(*sectionMap)[InputAction(inputID)] = actionName;

			// Log a successful mapping
			SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "Input::init() - Mapped %s to %s", actionName.c_str(), inputID.c_str());
		}
	}
}

void Input::register_callback(string action, ActionFuncPtr funcPtr)
{
	// Map the action name to the function pointer
	_actionFuncPtrMap[action] = funcPtr;

	// Log a successful mapping
	SDL_LogInfo(SDL_LOG_CATEGORY_INPUT,
		"Input::register_callback() - Mapped %s to function %i", action.c_str(), int(*(unsigned char *)(&funcPtr)));
}

void Input::enqueue_action(string inputID, bool state, int x, int y)
{
	// Create an InputAction object
	InputAction inputAction(inputID, state, x, y);

	// Add to the queue
	_inputActionQueue.push(inputAction);
}

void Input::execute_actions(float dt)
{
	InputAction inputAction;
	InputActionMap* currentMap;
	string actionName;
	StringVec::reverse_iterator j;
	while (!_inputActionQueue.empty())
	{
		// Grab the next action from the queue
		inputAction = _inputActionQueue.front();
		SDL_LogInfo(SDL_LOG_CATEGORY_INPUT,
		"Input::execute_actions() - Calling %s %s",
		inputAction.inputID.c_str(), (inputAction.state ? "down" : "up"));

		// Loop through the actionmaps until a valid mapping is found.
		for (j = _stack.rbegin(); j != _stack.rend(); ++j)
		{
			SDL_LogInfo(SDL_LOG_CATEGORY_INPUT,
			"Input::execute_actions() - Checking input map %s",
			j->c_str());

			// j is the name of the map. Grab a pointer to the map itself.
			currentMap = _map[*j];

			// If the action isn't in the map, go to the next map
			if (currentMap->find(inputAction) == currentMap->end())
			{
				SDL_LogWarn(SDL_LOG_CATEGORY_INPUT,
				"Input::execute_actions() - InputAction %s %s not mapped",
				inputAction.inputID.c_str(), (inputAction.state ? "down" : "up"));
				continue;
			}

			// if the action is in the map, execute it and break
			actionName = (*currentMap)[inputAction];

			// Ensure actionName is a key in _actionFuncPtrMap
			if (_actionFuncPtrMap.find(actionName) == _actionFuncPtrMap.end())
			{
				SDL_LogWarn(SDL_LOG_CATEGORY_INPUT,
				"Input::execute_actions() - Action %s not mapped to a function",
				actionName.c_str());
				continue;
			}

			// If peachy, call the function pointer and get out of the loop
			_actionFuncPtrMap[actionName](_game, dt, inputAction.state,
				inputAction.x, inputAction.y);
			break;
		}

		// Remove the action from the queue
		_inputActionQueue.pop();
	}
}
