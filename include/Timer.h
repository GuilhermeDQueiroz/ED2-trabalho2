#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace chrono;

class Timer
{
public:
	Timer() {};
	~Timer() {};

	void start();
	duration<double> stop();

private:
	time_point<high_resolution_clock> _startTime;
};

#endif // TIMER_H