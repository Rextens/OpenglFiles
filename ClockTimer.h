#pragma once

#include "Figures.h"
#include <ctime>

class ClockTimer
{
	float timer = 0;
	float timer2 = 0;

	unsigned int id = 0;

	unsigned short int tick = 0;
public:
	ClockTimer();
	ClockTimer(Save &save);

	~ClockTimer();
	void restart();
	float getTimeAsSeconds();
	float getTimeAsMiliseconds();

	float getTimeAsSeconds(Save &save);
	float getTimeAsMiliseconds(Save &save);
};

