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
	static void createFile(std::string wayToFile, std::error_code &error);
	static std::string encrypt(int &number);
	static bool getDistance(glm::vec3 &first, glm::vec3 &second, float distance);
	static bool mouseCollision(glm::vec3 &object, float distance);

	template<class Type, class Container> static bool noOne(Container container, Type type)
	{
		for (unsigned int i = 0; i < container.size(); ++i)
		{
			if (container[i] == type)
			{
				return false;
			}
		}
		return true;
	}
};

