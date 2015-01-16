#include <iostream>
#include <string>
#include <map>
#include <queue>

#include <jsoncpp/json/json.h>

#include "defines_constants_typedefs.h"
#include "input.h"
#include "named_stack.h"

using namespace std;

Input::Input(Game* game): _game(game)
{}

bool Input::init()
{
	// Get the controls section
	Json::Value controls = _game->config.root["controls"];

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
		cout << "section: " << sectionName << endl;

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
				cout << "Action " << actionName << " not mapped to a function" << endl;
				continue;
			}

			// Add the action binding to the map
			inputID = controls[sectionName][actionName].asString();
			(*sectionMap)[InputAction(inputID)] = actionName;

			cout << "Mapped " << actionName << " to " << inputID << endl;
		}
	}
}

void Input::register_callback(string action, ActionFuncPtr funcPtr)
{
	// Map the action name to the function pointer
	_actionFuncPtrMap[action] = funcPtr;

	cout << "Mapped " << action << " to function " << int(*(unsigned char *)(&funcPtr)) << endl;
}

void Input::enqueue_action(string inputID, bool state, int x, int y)
{
	_inputActionQueue.push(InputAction(inputID, state, x, y));
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
		cout << "Calling: " << inputAction.inputID << " " << (inputAction.state?"down":"up") << endl;

		// Loop through the actionmaps until a valid mapping is found.
		for (j = _stack.rbegin(); j != _stack.rend(); ++j)
		{
			string sss = *j;
			cout << "Checking input map: " << sss << endl;

			// j is the name of the map. Grab a pointer to the map itself.
			currentMap = _map[*j];

			// If the action isn't in the map, go to the next map
			if (currentMap->find(inputAction) == currentMap->end())
			{
				cout << "InputAction " << inputAction.inputID << " " << (inputAction.state?"down":"up") << " not mapped" << endl;
				continue;
			}

			// if the action is in the map, execute it and break
			actionName = (*currentMap)[inputAction];

			// Ensure actionName is a key in _actionFuncPtrMap
			if (_actionFuncPtrMap.find(actionName) == _actionFuncPtrMap.end())
			{
				cout << "Action " << actionName << " not mapped to a function" << endl;
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

/////////////

Game::Game():_input(0)
{}

Game::~Game()
{
	// Delete all the Inputs in the input map
	delete _input;
}

void Game::init()
{
	// Open the config file
	config.open();

	// Create an Input
	if (_input)
		delete _input;
	_input = new Input(this);

	// Register all the callbacks
	_input->register_callback("attack", attack);
	_input->register_callback("menu_clicked", menu_clicked);
	_input->register_callback("jump", jump);
	_input->register_callback("quit", quit);
	_input->register_callback("toggle_cursor", toggle_cursor);
	_input->register_callback("crouch", crouch);
/*  _input->register_callback("toggle_fullscreen", toggle_fullscreen); */

	// Initialize the input, which loads the keymap from config.json
	_input->init();

	// Load the main keymap into the input stack
	_input->push("main");
	_input->push("menu");
}

Input* Game::get_input(string name)
{
	// Return the input
	return _input;
}

/////////////

void jump(Game* game, float dt, bool state, int x, int y)
{
	cout << "jumping: " << dt << endl;
}

void attack(Game* game, float dt, bool state, int x, int y)
{
	cout << "attacking: " << dt << endl;
}

void crouch(Game* game, float dt, bool state, int x, int y)
{
	cout << "crouching: " << dt << endl;
}

void quit(Game* game, float dt, bool state, int x, int y)
{
	cout << "quitting: " << dt << endl;
}

void toggle_cursor(Game* game, float dt, bool state, int x, int y)
{
	cout << "toggle_cursor: " << dt << endl;
}

void menu_clicked(Game* game, float dt, bool state, int x, int y)
{
	cout << "UI Clicked: " << x << ", " << y << endl;
}

/////////////

int main(void)
{
	Game game;
	game.init();
	cout << "==========INPUT========" << endl;
/* 	game.get_input("main")->enqueue_action("mouse_1");
	game.get_input()->enqueue_action("mouse_1");
	game.get_input()->enqueue_action("mouse_2");
	game.get_input()->enqueue_action("mouse_1");
	game.get_input()->enqueue_action("mouse_2");
	game.get_input()->enqueue_action("Left Shift"); */
	game.get_input()->enqueue_action("mouse_1");
	game.get_input()->enqueue_action("mouse_1", false);
/* 	game.get_input()->enqueue_action("mouse_4");
	game.get_input()->enqueue_action("Escape"); */
	cout << "==========EXECUTE========" << endl;
	game.get_input()->execute_actions(1.234f);
	cout << "==========POP========" << endl;
	game.get_input()->pop();
	cout << "==========INPUT========" << endl;
	game.get_input()->enqueue_action("mouse_1");
	game.get_input()->enqueue_action("mouse_1", false);
	cout << "==========EXECUTE========" << endl;
	game.get_input()->execute_actions(1.234f);
	return 0;
}
