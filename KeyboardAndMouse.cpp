#include "KeyboardAndMouse.h"



KeyboardAndMouse::KeyboardAndMouse()
{
}
KeyboardAndMouse::~KeyboardAndMouse()
{
}
bool KeyboardAndMouse::oneKeyPressed(Window &window, int key)
{
	if (block == false && glfwGetKey(window.window, key))
	{
		flag = !flag;

		block = true;
	}
	else if (block == true && !glfwGetKey(window.window, key))
	{
		block = false;
	}
	return flag;
}
bool KeyboardAndMouse::oneButtonPressed(Window &window, int key)
{
	static bool block = false;
	static bool flag = false;

	if (block == false && glfwGetMouseButton(window.window, key))
	{
		flag = !flag;

		block = true;
	}
	else if (block == true && !glfwGetMouseButton(window.window, key))
	{
		block = false;
	}
	return flag;
}
void KeyboardAndMouse::closeWindow(Window &window)
{
	if (glfwGetKey(window.window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window.window, GL_TRUE);
		return;
	}
}
