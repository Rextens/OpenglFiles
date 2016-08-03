#include "Clock.h"


Clock::Clock()
{
	restart();
}
Clock::Clock(Save &save)
{
	static unsigned int nr = 0;
	
	nr = id;
	restart();

	tick = save.timers[nr];

	nr++;
}
Clock::~Clock()
{
}
void Clock::restart()
{
	tick = 0;
	timer2 = clock();
}
float Clock::getTimeAsSeconds()
{
	timer = clock();
	return (timer - timer2) / 1000;
}
float Clock::getTimeAsMiliseconds()
{
	timer = clock();
	return timer - timer2;
}

float Clock::getTimeAsSeconds(Save &save)
{
	timer = clock();
	save.timers[id] = (timer - timer2) + tick / 1000;
	return (timer - timer2) + tick / 1000;
}
float Clock::getTimeAsMiliseconds(Save &save)
{
	timer = clock();
	save.timers[id] = (timer - timer2) + tick;
	return (timer - timer2) + tick;
}
