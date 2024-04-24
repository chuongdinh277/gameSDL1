#include"Time.h"

Time_delay::Time_delay()
{
	start_tick = 0;
}
Time_delay::~Time_delay(){}
void Time_delay::Start()
{
	is_start = true;
	is_pause = false;
	start_tick = SDL_GetTicks();
}


int Time_delay::gettick()
{
	if (is_start == true)
	{
		return SDL_GetTicks() - start_tick;
	}
	return 0;
}

