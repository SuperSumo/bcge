#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

class Timer
{
	public:
		Timer();
		float restart();

	private:
		uint _startTime;
};

#endif
