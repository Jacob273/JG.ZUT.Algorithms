#pragma once

#include "ctime"

class Timer
{
	static clock_t startTime;
	static clock_t endTime;

public:
	static void Start();
	static void Stop();
	static double TimeSpent();
};



