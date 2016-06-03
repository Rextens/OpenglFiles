#include "ClockTimer.h"



ClockTimer::ClockTimer()
{
	restart();
}
ClockTimer::ClockTimer(Save &save)
{
	static unsigned int nr = 0;
	
	nr = id;
	restart();

	tick = save.timers[nr];

	nr++;
}
ClockTimer::~ClockTimer()
{
}
void ClockTimer::restart()
{
	tick = 0;
	timer2 = clock();
}
float ClockTimer::getTimeAsSeconds()
{
	timer = clock();
	return (timer - timer2) / 1000;
}
float ClockTimer::getTimeAsMiliseconds()
{
	timer = clock();
	return timer - timer2;
}

float ClockTimer::getTimeAsSeconds(Save &save)
{
	timer = clock();
	save.timers[id] = (timer - timer2) + tick / 1000;
	return (timer - timer2) + tick / 1000;
}
float ClockTimer::getTimeAsMiliseconds(Save &save)
{
	timer = clock();
	save.timers[id] = (timer - timer2) + tick;
	return (timer - timer2) + tick;
}
