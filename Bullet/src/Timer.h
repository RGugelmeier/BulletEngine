#pragma once

class Timer {
private:
	int startTicks; //Time when the timer started.
	int pausedTicks; //Ticks accumulated while the timer was paused.

	unsigned int prevTicks;
	unsigned int currentTicks;

	/* paused and started
		Timer's current status */
	bool paused;
	bool started;
public:
	/* Constructor and De-Constructor */
	Timer();
	~Timer();

	/* Functions to control timer */
	void Start();
	void Stop();
	void Pause();
	void Unpause();

	/* Get the timer's time */
	float GetTicks();

	/* Gets delta time. Used to easily see time */
	float GetDeltaTime() const;

	/* This is used to cap the fps. */
	unsigned int GetSleepTime(const unsigned int fps_) const;

	/* This updates the current and prev ticks variables every tick. */
	void UpdateFrameTicks();

	/* Checks the status of the timer */
	bool isStarted();
	bool isPaused();
};
