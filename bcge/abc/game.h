#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include "../shaderManager.h"

class Manager;
class Keyboard;

class Game
{
	public:

		Game(Manager* manager);
		virtual ~Game();

		Manager* get_manager();
		Keyboard* get_keyboard();

		void toggle_pause();

		virtual void load();
		virtual void update(float dt)=0;
		virtual void interp(float dt)=0;
		virtual void draw()=0;

	protected:

		Manager* _manager;
		bool _isPaused;
		Keyboard* _keyboard;
		ShaderManager shaderManager;

	private:

		Game();
};

#endif
