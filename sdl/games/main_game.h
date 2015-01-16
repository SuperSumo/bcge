#ifndef MAIN_GAME_H
#define MAIN_GAME_H

// TODO: Remove these includes
#include <GL/glew.h>
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

void jump(Game* game, float dt, bool state, int x, int y);
void crouch(Game* game, float dt, bool state, int x, int y);
void quit(Game* game, float dt, bool state, int x, int y);
void toggle_fullscreen(Game* game, float dt, bool state, int x, int y);
void toggle_menu(Game* game, float dt, bool state, int x, int y);
void menu_click(Game* game, float dt, bool state, int x, int y);
void attack(Game* game, float dt, bool state, int x, int y);

#endif
