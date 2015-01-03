// TODO: i don't need <iostream>
#include <iostream>
using namespace std;

#include <SDL2/SDL.h>

#include "defines_constants_typedefs.h"
#include "manager.h"
#include "window.h"
#include "renderer.h"
#include "abc/game.h"
#include "abc/input.h"
#include "timer.h"

using namespace std;

Manager::Manager():
	_window(0),
	_renderer(0),
	_game(0),
	_isRunning(false)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Manager::Manager()");
}

Manager::~Manager()
{
	// TODO: Write out settings to the json file before deleting objects
	delete _game;
	delete _window;
	delete _renderer;
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Manager::~Manager()");
	SDL_Quit();
}

bool Manager::init()
{
	// Set logging options
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Manager::init()");

	// According to the SDL docs/examples, initialization order is:
	// 1. SDL init			SDL_Init()
	// 1. set attributes	Renderer()
	// 2. create window		Window(); window->init()
	// 3. create context	renderer->init()

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"Manager::init() - SDL could not be initialized: %s\n",
			SDL_GetError());
		return false;
	}

	// Open the config file
	config.open("config.json");

	// Create the renderer, which sets attributes
	_renderer = new Renderer(this);

	// Create the window after the renderer
	_window = new Window(this);
	if (!_window->create_window())
		return false;

	// Initialize the renderer after window creation and initialization
	if (!_renderer->init())
		return false;

	return true;
}

void Manager::quit()
{
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Manager::quit()");
	_isRunning = false;
}

void Manager::load_game(Game* game)
{
	// You must initialize the game before loading it with this method.

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Manager::load_game()");

	// Delete the current game
	if (_game)
		delete _game;

	// Set the game
	_game = game;
}

void Manager::start_main_loop()
{
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Manager::start_main_loop()");

	// "Perfect Main Loop" references:
	// http://gafferongames.com/game-physics/fix-your-timestep/
	// http://en.sfml-dev.org/forums/index.php?topic=8996.0

	Timer timer;
	float accumulator = 0;
	float frameTime = 0;
	uint avoidSpiral = DT * 100;

	// Keep the manager alive until we are done
	_isRunning = true;
	while (_isRunning)
	{
		// Update the times and escape the "spiral of death"
		frameTime = timer.restart();
		if (frameTime > avoidSpiral)
			frameTime = avoidSpiral;
		accumulator += frameTime;

		// Only update the physics every DT seconds.
		while (accumulator >= DT)
		{
			// Do the physics simulation: collision detection, etc.
			_game->update(DT);
			accumulator -= DT;
		}

		// Handle events
		_handle_events();

		// Handle the input event queue
		_game->get_input()->_check_input(DT);

		// Just interpolate the physics simulation. Should be very fast.
		_game->interp(accumulator);

		// Render the game
		_renderer->render(_game);
	}
}

void Manager::_handle_events()
{
	SDL_Event event;
	SDL_Scancode scanCode;
	Uint8 button;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				quit();
				break;

			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
					_renderer->set_viewport(0, 0,
						event.window.data1, event.window.data2);
				break;

			case SDL_KEYDOWN:
				scanCode = event.key.keysym.scancode;
				if (!event.key.repeat)
					_game->get_input()->key_event(scanCode, true);
				break;

			case SDL_KEYUP:
				scanCode = event.key.keysym.scancode;
				_game->get_input()->key_event(scanCode, false);
				break;

			case SDL_MOUSEBUTTONDOWN:
				button = uint(event.button.button);
				_game->get_input()->button_event(button, true);
				break;

			case SDL_MOUSEBUTTONUP:
				button = uint(event.button.button);
				_game->get_input()->button_event(button, false);
				break;

			case SDL_MOUSEMOTION:
				// TODO: Move this to the input manager
				move_mouse(event.motion.xrel, event.motion.yrel);
				break;

			default:
				break;
		}
	}
}

void Manager::move_mouse(Sint32 xrel, Sint32 yrel)
{
	static bool wasMoved = true;
	wasMoved = !wasMoved;
	if (wasMoved)
		return;

	// If we are currently showing the cursor, don't move it back to the middle
	if (SDL_ShowCursor(-1) == 1)
		return;

	cout << "Mouse Moved: " << xrel << ", " << yrel << endl;
	int width, height;
	SDL_GetWindowSize(_window->get_id(), &width, &height);
	SDL_WarpMouseInWindow(_window->get_id(), width>>1, height>>1);
}

Window* Manager::get_window()
{
	return _window;
}

Renderer* Manager::get_renderer()
{
	return _renderer;
}

Game* Manager::get_game()
{
	return _game;
}
