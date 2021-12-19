#include "../include/Timer.h"

void Timer::start()
{
	_startTime = high_resolution_clock::now();
}

duration<double> Timer::stop()
{

	time_point<high_resolution_clock> end;

	end = high_resolution_clock::now();

	duration<double> elapsed_seconds = end - _startTime;
	return elapsed_seconds;
	//cout << "O tempo gasto foi: " << elapsed_seconds.count() << "s" << endl;
}