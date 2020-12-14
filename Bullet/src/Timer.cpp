#include "SDL.h"
#include "Timer.h"

Timer::Timer() : prevTicks(0), currentTicks(0) {

	startTicks = 0;
	pausedTicks = 0;

	paused = false;
	started = false;
}

Timer::~Timer() {}

void Timer::UpdateFrameTicks() {
	//Updates the previous and current tick variables every tick.
	prevTicks = currentTicks;
	currentTicks = SDL_GetTicks();
}

void Timer::Start() {
	//Fill previous and current tick variables.
	prevTicks = SDL_GetTicks();
	currentTicks = SDL_GetTicks();

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


// TO-DO
// SET IT SO WHEN THE TIMER IS PAUSED, IT ALSO PAUSES THE SCENE'S RENDING AND UPDATES
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

float Timer::GetTicks()
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

//Used for everythings Update() function. DeltaTime is used to keep the update function's time consistent between frames.
float Timer::GetDeltaTime() const
{
	//Gets delta time.
	return static_cast<float>(currentTicks - prevTicks) / 1000.0f;
}

//This function acts to set the fps to a limit. That way you can easily control the speed at which the timer performs.
unsigned int Timer::GetSleepTime(const unsigned int fps_) const
{
	unsigned int milliSecsPerFrame = 1000 / fps_;
	if (milliSecsPerFrame == 0) {
		return 0;
	}
	unsigned int sleepTime = milliSecsPerFrame - SDL_GetTicks();
	if (sleepTime > milliSecsPerFrame) {
		return milliSecsPerFrame;
	}
	return sleepTime;
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