#ifndef FRAME_TIMER_H
#define FRAME_TIMER_H

#pragma once
#include <Windows.h>

class FrameTimer
{
public:
	void init(int);
	int framesToUpdate();
	int getFPS();

private:
	LARGE_INTEGER timerFreq;
	LARGE_INTEGER timeNow;
	LARGE_INTEGER timePrevious;
	int requestedFPS;
	float intervalsPerFrame;
	float intervalsSinceLastUpdate;
};

#endif

