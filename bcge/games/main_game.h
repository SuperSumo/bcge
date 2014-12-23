#ifndef MAIN_GAME_H
#define MAIN_GAME_H

#include <gl/glew.h>
#include <SFML/Graphics.hpp>

#include "../abc/game.h"

class Manager;

class MainGame: public Game
{
	public:

		MainGame(Manager* manager);
		virtual ~MainGame();

		virtual void load();
		virtual void update(float dt);
		virtual void interp(float dt);
		virtual void draw();

	private:

		MainGame();

		// TODO: Delete all of this stuff
		GLuint _vbo;
		GLuint _cbo;

};

#endif
