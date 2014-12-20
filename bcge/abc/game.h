#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>

class Manager;
class Keyboard;

class Game
{
	public:

		Game(Manager* manager);
		~Game();

		Manager* get_manager();
		Keyboard* get_keyboard();

		void update(float dt);
		void interp(float dt);
		void toggle_pause();

	private:

		Game();

		Manager* _manager;
		bool _isPaused;
		Keyboard* _keyboard;
};

#endif
