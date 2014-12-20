#ifndef MANAGER_H
#define MANAGER_H

class Game;
class Window;
class Renderer;

class Manager
{
	public:

		Manager(Game* initialGame=0);
		~Manager();

		void load_game(Game* gameToSet);
		void quit();

		Window* get_window();
		Game* get_game();
		Renderer* get_renderer();

	private:

		Window* _window;
		Game* _game;
		Renderer* _renderer;
		bool _isRunning;
		void _main_loop();
		void _handle_events();
};

#endif
