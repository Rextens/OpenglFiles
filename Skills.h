#pragma once

#include <iostream>
#include "Window.h"
#include "Game.h"
#include "MouseAndKeyboard.h"

struct IsActivated
{
	bool book = false;
};

class Skills
{
	bool pushed = false;
	
public:
	IsActivated isActiveated;

	unsigned int nr = 0;
	
	std::string ability;

	Skills();
	~Skills();
	void dictionary(Window &window, Game &game);
	void sentence(Window &window, MouseAndKeyboard &MAK);

	std::vector<std::vector<std::string> > abilities;

	ClockTimer loader;
};

