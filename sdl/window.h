#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <SDL2/SDL.h>

#include "defines_constants_typedefs.h"

using namespace std;

class Manager;

class Window
{
	public:

		Window(Manager* manager, uint x=SDL_WINDOWPOS_CENTERED,
			uint y=SDL_WINDOWPOS_CENTERED, uint width=WINDOW_WIDTH,
			uint height=WINDOW_HEIGHT);
		~Window();

		SDL_Window* get_id() const;
		bool create_window();
		void toggle_fullscreen();

	private:

		Window();

		Manager* _manager;
		SDL_Window* _id;
		uint _x;
		uint _y;
		uint _width;
		uint _height;
		bool _isFullScreen;
};

#endif

// REFERENCE CODE:

// // Get current display mode of all displays.
// SDL_DisplayMode current;
// for(int i = 0; i < SDL_GetNumVideoDisplays(); ++i)
// {
// 	int should_be_zero = SDL_GetCurrentDisplayMode(i, &current);

// 	if(should_be_zero != 0)
// 		// In case of error...
// 		SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());

// 	else
// 		// On success, print the current display mode.
// 		SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz. \n", i, current.w, current.h, current.refresh_rate);
// }
