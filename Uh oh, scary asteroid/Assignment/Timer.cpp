#include "Timer.h"

Timer::Timer()
{
	//Ask CPU how many ticks per second
	QueryPerformanceFrequency(&timerFreq);

	//Since the PC was switched on, how many ticks?
	QueryPerformanceCounter(&timeNow);
	QueryPerformanceCounter(&timePrevious);
}

int Timer::secondsToUpdate()
{
	int secondsToUpdate = 0;
	QueryPerformanceCounter(&timeNow);

	//getting the delta time
	intervalsSinceLastUpdate = (float)timeNow.QuadPart - (float)timePrevious.QuadPart;
	secondsToUpdate = (int)(intervalsSinceLastUpdate / timerFreq.QuadPart);

	//If we are not updating any frames, keep the old previous timer count
	if (secondsToUpdate != 0)
	{
		QueryPerformanceCounter(&timePrevious);
	}
	return secondsToUpdate;
}