#ifndef MANAGER_H
#define MANAGER_H

class Game;
class Window;
class Renderer;

class Manager
{
	public:

		Manager();
		~Manager();

		void load_game(Game* gameToSet);
		void reload();

		Window* get_window();
		Renderer* get_renderer();
		Game* get_game();

	private:

		void _main_loop();
		void _handle_events();

		Window* _window;
		Renderer* _renderer;
		Game* _game;
		bool _mainLoopStarted;
};

#endif
