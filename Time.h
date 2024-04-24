#pragma once
#ifndef TIME_H
#define TIME_H
#include<SDL.h>

class Time_delay
{
public:
	Time_delay();
	~Time_delay();

	void Start();
	int gettick();
private:

	int start_tick;
	bool is_start;
	bool is_pause;
};

#endif // !TIME_H
