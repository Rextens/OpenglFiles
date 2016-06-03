#include "Timer.h"


Timer::Timer()
{
}
Timer::~Timer()
{
}
void Timer::dayAndNight(GLint &handle)
{
	if (dayCycle.getTimeAsSeconds() >= 0 && dayCycle.getTimeAsSeconds() <= 10)
	{
		if (dayNight.getTimeAsSeconds() > 0.1)
		{
			day += 0.01f;

			lightness = glm::vec3(day, day, day);
			glUniform3f(handle, lightness.x, lightness.y, lightness.z);
			if (day >= 1)
			{
				day = 1;
			}
			dayNight.restart();
		}
	}
	if (dayCycle.getTimeAsSeconds() >= 11 && dayCycle.getTimeAsSeconds() <= 20)
	{
		if (dayNight.getTimeAsSeconds() > 0.1)
		{
			day -= 0.01f;

			lightness = glm::vec3(day, day, day);
			glUniform3f(handle, lightness.x, lightness.y, lightness.z);
			if (day >= 1)
			{
				day = 1;
			}
			dayNight.restart();
		}
	}
	if (dayCycle.getTimeAsSeconds() > 20)
	{
		dayCycle.restart();
	}
}