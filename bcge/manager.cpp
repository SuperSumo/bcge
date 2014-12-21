#include <iostream>

#include "manager.h"

#include "abc/game.h"
#include "renderer.h"
#include "window.h"
#include "keyboard.h"
#include "defines_constants_typedefs.h"

using namespace std;

Manager::Manager():
	_game(0),
	_vShader(new Shader(GL_VERTEX_SHADER)),
	_fShader(new Shader(GL_FRAGMENT_SHADER))
{
	// Create the window first to get a valid OpenGL context
	_window = new Window(this);

	// Initialize OpenGL and a renderer, since an OpenGL context is open
	_renderer = new Renderer(this);

	// Load the game now that the window is created
	load_game(new Game(this));

	// Start the main loop
	_main_loop();
}

void Manager::draw()
{
	// glColor3f(0.3f, 0.6f, 0.9f);
	// glBegin(GL_POINTS);
	// glVertex3f(0.0f, 0.0f, 0.0f);
	// glEnd();

	glUseProgram(_shaderProgID);

	GLuint vboLoc = glGetAttribLocation(_shaderProgID, "inVertex");
	GLuint cboLoc = glGetAttribLocation(_shaderProgID, "inColor");

	glEnableVertexAttribArray(vboLoc);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glVertexAttribPointer(vboLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(cboLoc);
	glBindBuffer(GL_ARRAY_BUFFER, _cbo);
	glVertexAttribPointer(cboLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_POINTS, 0, 1);

	glDisableVertexAttribArray(vboLoc);
	glDisableVertexAttribArray(cboLoc);
	glUseProgram(0);
}

Manager::~Manager()
{
	delete _vShader;
	delete _fShader;
	delete _game;
	delete _renderer;
	delete _window;
}

void Manager::load_game(Game* game)
{
	// Delete the current game
	if (_game)
		delete _game;

	// Set the game
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

void Manager::_main_loop()
{

	////////////////
	// TODO: MOVE ALL THIS CODE OUT OF HERE

	// Load the model data. Delete this and move into a game loading thing.
	float verts[3] = {0.0f, 0.0f, 0.0f};
	float colors[3] = {0.3f, 0.6f, 0.9f};
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glGenBuffers(1, &_cbo);
	glBindBuffer(GL_ARRAY_BUFFER, _cbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	// // TODO: I need to finish the shader manager first.
	// //	_shaderManager->add_shader("vertex.glsl");
	_vShader->load("shaders/vertex.glsl");
	_fShader->load("shaders/fragment.glsl");

	_shaderProgID = glCreateProgram();
	glAttachShader(_shaderProgID, _vShader->get_id());
	glAttachShader(_shaderProgID, _fShader->get_id());
	glLinkProgram(_shaderProgID);

	////////////////


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

		// Check the held down keys
		_game->get_keyboard()->check_keys(dt);

		// Just interpolate the physics simulation. Should be very fast.
		_game->interp(accumulator / dt);

		// Draw the current state of everything.
		_renderer->render();
	}
}

void Manager::_handle_events()
{
	sf::Event event;
	while (_window->pollEvent(event))
	{
		switch (event.type)
		{
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
