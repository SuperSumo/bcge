#include <string>

#include <SDL2/SDL.h>

#include "input.h"
#include "../abc/game.h"
#include "../manager.h"

using namespace std;

Input::Input(Game* game):
	_game(game)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "Input::Input()");
}

Game* Input::get_game()
{
	return _game;
}

void Input::key_event(SDL_Scancode key, bool state)
{
	_keyQueue.push(KeyState(key, state));
}

void Input::button_event(Uint8 button, bool state)
{
	_buttonQueue.push(ButtonState(button, state));
}

void Input::_check_input(float dt)
{
	// Check the keyboard keys
	KeyState key;
	while (!_keyQueue.empty())
	{
		key = _keyQueue.front();
		_check_key(key.first, key.second, dt);
		_keyQueue.pop();
	}

	// Check the mouse buttons
	ButtonState button;
	while (!_buttonQueue.empty())
	{
		button = _buttonQueue.front();
		_check_button(button.first, button.second, dt);
		_buttonQueue.pop();
	}
}

void Input::_add_key_action(string action, SDL_Scancode defaultKey,
	bool state)
{
	// Get the key from the config file
	string name(SDL_GetScancodeName(defaultKey));
	string k = _game->get_manager()->config.root.get(action, name).asString();

	// Set the key again. If the key wasn't initially set, it is now.
	_game->get_manager()->config.root[action] = k;

	// Add keymap with the actual scancode
	SDL_LogInfo(SDL_LOG_CATEGORY_INPUT,
		"Input::_add_action() - Added %s as %s",
		k.c_str(), action.c_str());
	_keyMap[KeyState(SDL_GetScancodeFromName(k.c_str()), state)] = action;
}

void Input::_add_button_action(string action, Uint8 defaultButton,
	bool state)
{
	// Get the button from the config file
	uint k = _game->get_manager()->config.root.get(action, \
		defaultButton).asUInt();

	// Set the button again. If the button wasn't initially set, it is now.
	_game->get_manager()->config.root[action] = k;

	// Add buttonmap with the actual scancode
	SDL_LogInfo(SDL_LOG_CATEGORY_INPUT,
		"Input::_add_action() - Added %i as %s", k, action.c_str());
	_buttonMap[ButtonState(k, state)] = action;
}

void Input::_check_key(SDL_Scancode key, bool state, float dt)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "Key %s %s", SDL_GetScancodeName(key),
		(state ? "is down" : "is up"));

	// Call the function pointer associated with the action
	// Get the action from the key -> action map
	KeyState keyState(key, state);

	// If the key isn't in the map abort
	if (_keyMap.find(keyState) == _keyMap.end())
		return;

	// If it is, save it
	string action = _keyMap[keyState];

	// Call the derived class' execute method
	_execute_action(action, dt);
}

void Input::_check_button(Uint8 button, bool state, float dt)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "Button %i %s", button,
		(state ? "is down" : "is up"));

	// Call the function pointer associated with the action
	// Get the action from the key -> action map
	ButtonState buttonState(button, state);

	// If the button isn't in the map abort
	if (_buttonMap.find(buttonState) == _buttonMap.end())
		return;

	// If it is, save it
	string action = _buttonMap[buttonState];

	// Call the derived class' execute method
	_execute_action(action, dt);
}
