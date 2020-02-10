#pragma once
class Timer
{
	Timer() : startTime(0), endTime(0) {};  // Private so that it can  not be called
	Timer(Timer const&) {};             // copy constructor is private
	Timer& operator=(Timer const&) {};  // assignment operator is private
	static Timer* instance;
	int startTime;
	int endTime;

public:
	static Timer* Instance();
	void Start();
	void Stop();
	double TimeSpent();
};

#pragma once