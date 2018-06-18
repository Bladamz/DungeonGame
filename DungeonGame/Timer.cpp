#include "Timer.h"

Timer::Timer()
{
	startTicks = 0;
	started = false;
}

void Timer::start()
{
	//Start the timer
	started = true;

	//Get the current clock time
	startTicks = SDL_GetTicks();
}

void Timer::stop()
{
	//Stop the timer
	started = false;
	//Clear tick variables
	startTicks = 0;
}

Uint32 Timer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

	//If the timer is running
	if (started)
	{
		time = SDL_GetTicks() - startTicks;
	}

	return time;
}

bool Timer::isStarted()
{
	//Timer is running and paused or unpaused
	return started;
}
