#include "Auxiliary.h"

Auxiliary::Auxiliary()
{
}
Auxiliary::~Auxiliary()
{
}
std::string Auxiliary::encrypt(std::string &inscription)
{
	std::string word = "";
	for (unsigned short int i = 0; i < inscription.size(); i++)
	{
		word += (inscription[i] - 3) ^ 47;
	}
	return word;
}
std::string Auxiliary::decypt(std::string &inscription)
{
	std::string word = "";
	for (unsigned short int i = 0; i < inscription.size(); i++)
	{
		word += (inscription[i] ^ 47) + 3;
	}
	return word;
}
void Auxiliary::createFile(std::string wayToFile, std::error_code error)
{
	if (!std::experimental::filesystem::create_directory(wayToFile, error));
	{
		std::cout << error.message() << std::endl;
	}
}
std::string Auxiliary::encrypt(int &number)
{
	std::string encryptString = std::to_string(number);
	int *encryptInt = new int[encryptString.size()];
	char *encryptChar = new char[encryptString.size()];

	for (int i = 0; i < encryptString.size(); i++)
	{
		encryptChar[i] = encryptString[i];
		std::cout << atoi(&encryptString[i]) << std::endl;
	}

	return encryptString;
}
bool Auxiliary::getDistance(glm::vec3 first, glm::vec3 second, float distance)
{
	float distanceNow = pow(pow(first.x - second.x, 2.0f) + pow(first.y - second.y, 2.0f) + pow(first.z - second.z, 2.0f), 0.5f);

	if (distanceNow <= distance)
	{
		return true;
	}
	else
	{
		return false;
	}
}