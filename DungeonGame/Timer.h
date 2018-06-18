#pragma once

#include <SDL.h>

class Timer
{
public:
	//Initializes variables
	Timer();

	//clock actions
	void start();
	void stop();
	Uint32 getTicks();
	bool isStarted();
private:
	//The clock time when the timer started
	Uint32 startTicks;
	bool started;
};

