#include "Timer.h"
#include "ctime"

Timer* ::Timer::instance;
Timer* Timer::Instance()
{
	if (!instance)
		instance = new Timer();

	return instance;
}

void Timer::Start()
{
	startTime = clock();
}

void Timer::Stop()
{
	endTime = clock();
}

double Timer::TimeSpent()
{
	return (double)(endTime - startTime) / CLOCKS_PER_SEC;
}