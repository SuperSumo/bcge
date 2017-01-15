#include <SDL2/SDL.h>

#include "timer.h"

Timer::Timer():
	_startTime(SDL_GetTicks())
{}

float Timer::restart()
{
	float delta = (SDL_GetTicks() - _startTime) / 1000.f;
	_startTime = SDL_GetTicks();
	return delta;
}
