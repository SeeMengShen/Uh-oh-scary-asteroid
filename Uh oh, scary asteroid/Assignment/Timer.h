#ifndef TIMER_H
#define TIMER_H

#pragma once
#include <Windows.h>

class Timer
{
public:
	Timer();
	int secondsToUpdate();

private:
	LARGE_INTEGER timerFreq;
	LARGE_INTEGER timeNow;
	LARGE_INTEGER timePrevious;
	float intervalsSinceLastUpdate;
};

#endif // !TIMER_H