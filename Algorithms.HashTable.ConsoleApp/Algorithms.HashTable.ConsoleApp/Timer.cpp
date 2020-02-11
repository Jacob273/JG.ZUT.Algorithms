#include "Timer.h"

void Timer::Start()
{
	Timer::startTime = clock();
}

void Timer::Stop()
{
	endTime = clock();
}

double Timer::TimeSpent()
{
	return (double)(endTime - startTime) / CLOCKS_PER_SEC;
}

clock_t Timer::endTime = 0;
clock_t Timer::startTime = 0;