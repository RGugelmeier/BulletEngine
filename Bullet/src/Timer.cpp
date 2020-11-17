#include "SDL.h"
#include "Timer.h"

Timer::Timer() {
	//prevTicks = 0;
	//currTicks = 0;

	startTicks = 0;
	pausedTicks = 0;

	paused = false;
	started = false;
}

Timer::~Timer() {}

/*void Timer::UpdateFrameTicks() {
	prevTicks = currTicks;
	currTicks = SDL_GetTicks();
}*/

void Timer::Start() {
	/*prevTicks = SDL_GetTicks();
	currTicks = SDL_GetTicks();*/

	//Start the timer
	started = true;

	//Unpause the timer
	paused = false;

	//Get the current clock time
	startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

void Timer::Stop()
{
	//Stop the timer
	started = false;

	//Unpause the timer
	paused = false;

	//Clear tick variables
	startTicks = 0;
	pausedTicks = 0;
}

void Timer::Pause()
{
	//If the timer is running and isn't already paused
	if (started && !paused)
	{
		//Pause the timer
		paused = true;

		//Calculate the paused ticks
		pausedTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
	}
}

void Timer::Unpause()
{
	//If the timer is running and paused
	if (started && paused)
	{
		//Unpause the timer
		paused = false;

		//Reset the starting ticks
		startTicks = SDL_GetTicks() - pausedTicks;

		//Reset the paused ticks
		pausedTicks = 0;
	}
}

Uint32 Timer::GetTicks()
{
	//The actual timer time
	Uint32 time = 0;

	//If the timer is running
	if (started)
	{
		//If the timer is paused
		if (paused)
		{
			//Return the number of ticks when the timer was paused
			time = pausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - startTicks;
		}
	}

	return time;
}

bool Timer::isStarted()
{
	//Timer is running and paused or unpaused
	return started;
}

bool Timer::isPaused()
{
	//Timer is running and paused
	return paused && started;
}

/*float Timer::GetDeltaTime() const {
	return (float(currTicks - prevTicks)) / 1000.0f;
}

int Timer::GetSleepTime(const int fps) const {
	int milliSecsPerFrame = 1000 / fps;
	if (milliSecsPerFrame == 0) {
		return 0;
	}

	int sleepTime = milliSecsPerFrame - (SDL_GetTicks() - currTicks);
	if (sleepTime > milliSecsPerFrame) {
		return milliSecsPerFrame;
	}

	return sleepTime;
}*/