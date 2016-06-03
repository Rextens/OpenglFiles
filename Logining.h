#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <experimental\filesystem>

#include "Window.h"
#include "Auxiliary.h"

class Logining
{
public:
	std::string loginNow;

	bool logining = false;

	Logining();
	~Logining();
	void loadLogins(std::string logins);
	void registry(std::string wayToFile);
};

