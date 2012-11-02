#include <SFML/Window.hpp>
#include "keyboard.h"
#include "game.h"
#include "renderer.h"
#include "manager.h"
#include "window.h"
#include "camera.h"
#include <iostream>
using namespace std;

Keyboard::Keyboard(Game* game): game(game)
{}

Game* Keyboard::get_game()
{
	return game;
}

void Keyboard::key_released(sf::Keyboard::Key key)
{
	// A single key click checker
	switch (key)
	{
		case sf::Keyboard::Escape:
		case sf::Keyboard::Q:
			get_game()->quit();
			break;
		case sf::Keyboard::F:
			get_game()->get_manager()->get_window()->toggle_fullscreen();
			break;
		case sf::Keyboard::P:
			get_game()->toggle_pause();
			break;
		case sf::Keyboard::R:
			get_game()->get_renderer()->init_gl();
			break;
		default:
			break;
	}
}

void Keyboard::check_keys(float dt)
{
	// If keys are held down, the check goes here.
	// I need multiple IF statements here to check all the keys

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
		get_game()->get_camera()->change_fov(-10.0f*dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))
		get_game()->get_camera()->change_fov(10.0f*dt);
}
