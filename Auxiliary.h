#pragma once

#include <sstream>
#include <experimental\filesystem>
#include <iostream>
#include <glm.hpp>

class Auxiliary
{
public:
	Auxiliary();
	~Auxiliary();
	static std::string encrypt(std::string &inscription);
	static std::string decypt(std::string &inscription);
	static void createFile(std::string wayToFile, std::error_code error);
	static std::string encrypt(int &number);
	static bool getDistance(glm::vec3 first, glm::vec3 second, float distance);

};

