#ifndef TIMER_H
#define TIMER_H


class Timer {
private:
	int startTicks; //Time when the timer started.
	int pausedTicks; //Ticks accumulated while the timer was paused.

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
	Uint32 GetTicks();

	/* Checks the status of the timer */
	bool isStarted();
	bool isPaused();

	/*void UpdateFrameTicks();
	float GetDeltaTime() const;
	int GetSleepTime(const int fps) const;*/
};


#endif
