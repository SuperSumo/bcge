#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "defines.h"

#include <glm/glm.hpp>

#include <iostream>
using namespace std;
#include "game.h"
#include "window.h"
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "camera.h"
#include "object.h"
#include "instance.h"
#include "constants.h"

#include "objects/cube.h"
#include "objects/generic.h"
#include "instances/cube.h"

Game::Game(Manager* manager):
	manager(manager), isRunning(true), isPaused(false), camera(0)
{
	keyboard = new Keyboard(this);
	renderer = new Renderer(this);
}

Game::~Game()
{
	delete keyboard;
	delete renderer;

	// Delete each object in the object list, to call each object's destructor.
	for (vector<Object*>::iterator i=objects.begin(); i!=objects.end(); i++)
		delete *i;
	// Then, clear the list and delete each pointer.
	objects.clear();

	// Ditto with the instance list
	vector<Instance*>::iterator i;
	for (i=instances.begin(); i!=instances.end(); i++)
		delete *i;
	instances.clear();
}

Manager* Game::get_manager()
{
	return manager;
}

Keyboard* Game::get_keyboard()
{
	return keyboard;
}

Renderer* Game::get_renderer()
{
	return renderer;
}

Camera* Game::get_camera()
{
	return camera;
}

void Game::update(float dt)
{
	// Grab any new held down
	keyboard->check_keys(dt);
	// Update all the current instances of objects
	vector<Instance*>::iterator i;
	if (!isPaused)
		for (i=instances.begin(); i!=instances.end(); i++)
			(*i)->update(dt);
	// Render!
	renderer->render(instances);
}

void Game::load()
{
	// TODO: Finish the ShaderManager class

	// Load the game's objects
//	cout << "Game::load() - creating the objects" << endl;
	objects.push_back(new GenericObject(this));
	objects.push_back(new CubeObject(this));

	// Now create a Camera instance
//	cout << "Game::load() - creating the camera" << endl;
	camera = new Camera(objects.at(0),
			glm::vec3(0,0,-4),
			glm::vec3(0,0,0),
			glm::vec3(0,0,0),
			glm::vec3(0,0,0),
			glm::vec3(-51,41,0)
			);
	instances.push_back(camera);

	// Add a couple cubes
//	cout << "Game::load() - creating cube instances" << endl;
	instances.push_back(new CubeInstance(objects.at(1),
			glm::vec3(1,0,0),
			glm::vec3(0,0,0),
			glm::vec3(0,0,0),
			glm::vec3(0,0,0),
			glm::vec3(360,1.7,1.97)));
	instances.push_back(new CubeInstance(objects.at(1),
			glm::vec3(-2,0,0),
			glm::vec3(0,0,0),
			glm::vec3(0,0,0),
			glm::vec3(0,0,0),
			glm::vec3(-360,1.7,1.97)));
}

void Game::run()
{
	sf::Event event;
	Window* window = get_manager()->get_window();
	// Use a boolean to make sure the openGL context is valid for cleanup.
	sf::Time dt;
	sf::Time prev = clock.restart();
	while (isRunning)
	{
		get_manager()->get_window()->display();
//		cout << "FPS: " << int(1.0f/dt.asSeconds()) << endl;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					isRunning = false;
					break;
				case sf::Event::Resized:
					window->resize(event.size.width, event.size.height);
					break;
				case sf::Event::KeyReleased:
					// For one time only key events
					keyboard->key_released(event.key.code);
					break;
				default:
					break;
			}
		}
		dt = clock.restart() - prev;
		update(dt.asSeconds());
		prev = clock.restart();
	}
}

void Game::toggle_pause()
{
	isPaused = !isPaused;
}

void Game::quit()
{
	isRunning = false;
}
