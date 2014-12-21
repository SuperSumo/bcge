#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>

#include <gl/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "defines_constants_typedefs.h"

using namespace std;

class Manager;

class Window: public sf::Window
{
	public:

		Window(Manager* manager, string title=TITLE, uint w=400, uint h=300);
		Manager* get_manager();

		void create_window();
		void resize(uint width, uint height);
		void toggle_fullscreen();

	private:

		Window();

		Manager* _manager;
		uint _width;
		uint _height;
		string _title;
		bool _isFullScreen;
};

#endif
