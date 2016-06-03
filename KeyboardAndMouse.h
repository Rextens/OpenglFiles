#pragma once

#include "Window.h"

class KeyboardAndMouse
{
private:
	bool block = false;
	bool flag = false;
public:
	KeyboardAndMouse();
	~KeyboardAndMouse();


	bool oneKeyPressed(Window &window, int key);
	bool oneButtonPressed(Window &window, int key);
	void closeWindow(Window &window);
};

