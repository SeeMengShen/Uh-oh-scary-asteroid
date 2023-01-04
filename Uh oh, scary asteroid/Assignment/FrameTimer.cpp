#include "FrameTimer.h"
#include <iostream>
using namespace std;

void FrameTimer::init(int fps)
{
	//Ask CPU how many ticks per second
	QueryPerformanceFrequency(&timerFreq);

	//Since the PC was switched on, how many ticks?
	QueryPerformanceCounter(&timeNow);
	QueryPerformanceCounter(&timePrevious);

	//init fps time info
	requestedFPS = fps;

	//The number of intervals in the given
	//timer, per frame at the requested rate.
	intervalsPerFrame = ((float)timerFreq.QuadPart / requestedFPS);
}

int FrameTimer::framesToUpdate()
{
	int framesToUpdate = 0;
	QueryPerformanceCounter(&timeNow);

	//getting the delta time
	intervalsSinceLastUpdate = (float)timeNow.QuadPart - (float)timePrevious.QuadPart;
	framesToUpdate = (int)(intervalsSinceLastUpdate / intervalsPerFrame);

	//If we are not updating any frames, keep the old previous timer count
	if (framesToUpdate != 0)
	{
		QueryPerformanceCounter(&timePrevious);
	}
	return framesToUpdate;

}

int FrameTimer::getFPS()
{
	return requestedFPS;
}
