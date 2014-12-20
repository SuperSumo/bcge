#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <sstream>
#include <vector>

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

#include "defines.h"

using namespace std;

class Manager;

class Renderer
{
	public:

		Renderer(Manager* manager);
		~Renderer();
		Manager* get_manager();
		void init_gl();
		void draw();

	private:

		Renderer();

		Manager* _manager;
};

#endif
