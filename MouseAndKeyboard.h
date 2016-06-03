#pragma once
#include "Window.h"
#include <iostream>
#include <glfw3.h>
#include <map>

class MouseAndKeyboard
{
private:
	std::map<int, int> keyBoard;
	std::map<int, int> buttonBoard;

	std::map<int, bool> keyboardFlags;
	std::map<int, bool> mouseFlags;

	std::string sentence = "";
	std::string sentence2 = "";
public:
	MouseAndKeyboard();
	~MouseAndKeyboard();
	bool oneKeyPressed(Window &window, int key);
	bool oneButtonPressed(Window &window, int key);
	bool permaKeyPressed(Window &window, int key);
	bool permaButtonPressed(Window &window, int key);

	int x()
	{
		return 1;
		std::cout << "x";
	}

	void closeWindow(Window &window);
	std::string getKeybord(Window &window);
};

