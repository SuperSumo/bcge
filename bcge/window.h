#ifndef WINDOW_H_
#define WINDOW_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
using namespace std;
#include "defines.h"

class Manager;

class Window: public sf::Window
{
	public:

		Window(Manager* manager, int argc, char** argv,
				string title=TITLE, uint w=400, uint h=300);
		Manager* get_manager();

		void init_gl();
		void init_glew();

		void create_window();
		void resize(uint width, uint height);
		void toggle_fullscreen();
		uint width();
		uint height();
		float get_framerate() const;

	private:

		Window();
		Manager* manager;
		int argc;
		char** argv;
		uint w,h;
		string title;
		bool isFullScreen;
		sf::VideoMode fullScreenMode;
		float framerate;
};

#endif /* WINDOW_H_ */
