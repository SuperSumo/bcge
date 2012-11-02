#ifndef RENDERER_H_
#define RENDERER_H_

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <sstream>
using namespace std;
#include <vector>
#include "defines.h"

class Game;
class Renderer;
class Instance;

class Renderer
{
	public:

		Renderer(Game* game);
		~Renderer();
		Game* get_game();
		void init_gl();
		void render(vector<Instance*> instances);
		// TODO: Get rid of this!
		GLuint progID;

	private:

		Renderer();
		Game* game;
};

#endif /* RENDERER_H_ */
