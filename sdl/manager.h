#ifndef MANAGER_H
#define MANAGER_H

#include <SDL2/SDL.h>

#include "config.h"

class Window;
class Renderer;
class Game;

class Manager
{
	public:

		Manager();
		~Manager();

		bool init(); // Used so the constructor fully forms the object
		void quit();

		void load_game(Game* game);
		void start_main_loop();

		Window* get_window();
		Renderer* get_renderer();
		Game* get_game();

		Config config;

	private:

		void _handle_events();

		// TODO: Delete this
		void move_mouse(Sint32 xrel, Sint32 yrel);

		Window* _window;
		Renderer* _renderer;
		Game* _game;

		bool _isRunning;
};

#endif
