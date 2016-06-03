#pragma once

#include <GL\glew.h>
#include <glm.hpp>
#include <glfw3.h>
#include "ClockTimer.h"

class Timer
{
	float day;
	ClockTimer dayNight;
	ClockTimer dayCycle;
	glm::vec3 lightness;

public:
	Timer();
	~Timer();
	void dayAndNight(GLint &handle);
};

