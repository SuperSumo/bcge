#ifndef MAIN_GAME_H
#define MAIN_GAME_H

// TODO: Remove these includes
#include <gl/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "../abc/game.h"

class Manager;

class MainGame: public Game
{
	public:

		MainGame(Manager* manager);
		virtual ~MainGame();

		virtual bool init();
		virtual void update(float dt);
		virtual void interp(float dt);

		// TODO: Remove this method
		virtual void draw_delete_me();

	private:

		MainGame();

		// TODO: Delete these
		GLuint gProgramID;
		GLint gVertexPos2DLocation;
		GLuint gVBO;
		GLuint gIBO;
};

#endif
