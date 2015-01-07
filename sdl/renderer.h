#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "defines_constants_typedefs.h"

class Manager;
class Game;

class Renderer
{
	public:

		Renderer(Manager* manager);
		~Renderer();

		bool init();
		void render(Game* game);
		void set_viewport(uint x, uint y, uint width, uint height);

	private:

		Renderer();

		Manager* _manager;
		SDL_GLContext _context;
};

#endif
