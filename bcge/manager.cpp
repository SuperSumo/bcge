#include <iostream>

#include "manager.h"

#include "abc/game.h"
#include "renderer.h"
#include "window.h"
#include "keyboard.h"
#include "defines_constants_typedefs.h"

using namespace std;

Manager::Manager(Game* initialGame): _isRunning(true)
{
	// Create the window first to get a valid OpenGL context
	_window = new Window(this);
	// Initialize OpenGL
	_renderer = new Renderer(this);
	// Load the game
	load_game(initialGame ? initialGame : new Game(this));
	// Start the main loop
	_main_loop();
}

Manager::~Manager()
{
	delete _game;
	delete _renderer;
	delete _window;
}

void Manager::load_game(Game* game)
{
	_game = game;
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

void Manager::quit()
{
	_window->close();
}

void Manager::_main_loop()
{
	// "Perfect Main Loop" references:
	// http://gafferongames.com/game-physics/fix-your-timestep/
	// http://en.sfml-dev.org/forums/index.php?topic=8996.0

	sf::Clock clock;
	float currentTime = clock.getElapsedTime().asSeconds();
	float newTime = clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;
	float frameTime = 0.0f;

	// Keep the manager alive until we are done
	while (_window->isOpen())
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

		// Just interpolate the physics simulation. Should be very fast.
		_game->interp(accumulator / dt);

		// Draw the current state of everything.
		_renderer->draw();
	}
}

void Manager::_handle_events()
{
	sf::Event event;
	while (_window->pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				_isRunning = false;
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
