#include <iostream>

#include "manager.h"

#include "abc/game.h"
#include "renderer.h"
#include "window.h"
#include "abc/keyboard.h"
#include "defines_constants_typedefs.h"

using namespace std;

Manager::Manager():
	_game(0),
	_mainLoopStarted(false),
	_isRunning(false)
{
	// Create the window first to get a valid OpenGL context
	_window = new Window(this);

	// Initialize OpenGL and a renderer, since an OpenGL context is open
	_renderer = new Renderer(this);
}

Manager::~Manager()
{
	delete _game;
	delete _renderer;
	delete _window;
}

void Manager::quit()
{
	_isRunning = false;
}

void Manager::load_game(Game* game)
{
	cout << "Manager::load_game()" << endl;

	// Delete the current game
	if (_game)
		delete _game;

	// Set and load the game
	_game = game;
	_game->load();

	// Start the main loop if it isn't already running
	if (!_mainLoopStarted)
		_main_loop();
}

void Manager::reload()
{
	// Since the window was closed we need to re-initilize opengl and reload
	// all the game stuff
	cout << "Manager::reload()" << endl;
	_renderer->initialize();
	if (_game)
		_game->load();
}

Game* Manager::get_game()
{
	return _game;
}

Window* Manager::get_window()
{
	return _window;
}

Renderer* Manager::get_renderer()
{
	return _renderer;
}

void Manager::_main_loop()
{
	cout << "Manager::_main_loop" << endl;

	// Don't restart the mainloop if a new game is loaded
	_mainLoopStarted = true;

	// "Perfect Main Loop" references:
	// http://gafferongames.com/game-physics/fix-your-timestep/
	// http://en.sfml-dev.org/forums/index.php?topic=8996.0

	sf::Clock clock;
	float currentTime = clock.getElapsedTime().asSeconds();
	float newTime = clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;
	float frameTime = 0.0f;

	// Keep the manager alive until we are done
	_isRunning = true;
	while (_isRunning)
	{
		// Update the times and escape the "spiral of death"
		newTime = clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;
		float avoidSpiral = dt * 10;
		if (frameTime > avoidSpiral)
			frameTime = avoidSpiral;
		currentTime = newTime;
		accumulator += frameTime;

		// Only update the physics every dt seconds.
		while (accumulator >= dt)
		{
			// Do the physics simulation: collision detection, etc.
			_game->update(dt);
			accumulator -= dt;
		}

		// Handle user input
		_handle_events();

		// Check the held down keys
		_game->get_keyboard()->_check_keys(dt);

		// Just interpolate the physics simulation. Should be very fast.
		_game->interp(accumulator / dt);

		// Draw the current state of everything.
		_renderer->render();
	}
	cout << "DONE!" << endl;
}

void Manager::_handle_events()
{
	sf::Event event;
	while (_window->pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				quit();
				break;

			case sf::Event::Resized:
				_window->resize(event.size.width, event.size.height);
				break;

			case sf::Event::KeyPressed:
				_game->get_keyboard()->key_pressed(event.key.code);
				break;

			case sf::Event::KeyReleased:
				_game->get_keyboard()->key_released(event.key.code);
				break;

			default:
				break;
		}
	}
}
