#include <string>

#include "main_input.h"
#include "../abc/game.h"
#include "../manager.h"
#include "../window.h"

using namespace std;

MainInput::MainInput(Game* game):
	Input(game)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "MainInput::MainInput()");
}

bool MainInput::init()
{
	// Action name, default key, <true=down, false=up>, function pointer
	_add_key_action("quit", SDL_SCANCODE_Q, true);
	_add_key_action("toggle_fullscreen", SDL_SCANCODE_F, true);
	_add_key_action("toggle_cursor", SDL_SCANCODE_ESCAPE, true);

	// Add mouse button actions
	_add_button_action("mouse_clicked", 1, true);

	// Associate the action to a function
	_actionMap["quit"] = &MainInput::_quit;
	_actionMap["toggle_fullscreen"] = &MainInput::_toggle_fullscreen;
	_actionMap["toggle_cursor"] = &MainInput::_toggle_cursor;
	_actionMap["mouse_clicked"] = &MainInput::_mouse_clicked;
}

void MainInput::_execute_action(string action, float dt)
{
	// Check if the mapping has a function
	if (_actionMap.find(action) == _actionMap.end())
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_INPUT, "Action %s has no function",
			action.c_str());
		return;
	}

	// Execute the mapped method
	(this->*(_actionMap[action]))(dt);
}

void MainInput::_quit(float dt)
{
	_game->get_manager()->quit();
}

void MainInput::_toggle_fullscreen(float dt)
{
	_game->get_manager()->get_window()->toggle_fullscreen();
}

void MainInput::_toggle_cursor(float dt)
{
	SDL_bool cursorShown = SDL_bool((SDL_ShowCursor(-1) == 1));
	SDL_ShowCursor(!cursorShown);
	SDL_Window* id = _game->get_manager()->get_window()->get_id();
	SDL_SetWindowGrab(id, cursorShown);
}

void MainInput::_mouse_clicked(float dt)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "MainInput::mouse_clicked");
	if (SDL_bool((SDL_ShowCursor(-1) == 1))) // If the cursor is shown
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "UI (%i,%i)", x, y);
	}
	else
		SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "Attack!");
}
