#pragma once

#include "Figures.h"
#include "ClockTimer.h"
#include "Auxiliary.h"

#include <cmath>
#include <ctime>
#include <random>

class UnderFunctions
{
public:
	UnderFunctions();
	~UnderFunctions();
	glm::vec3 randomPosition(std::mt19937 &rand);
	glm::vec3 randomPosition(std::mt19937 &rand, glm::vec2 &bonusRandom);
	int type(int min, int max, std::mt19937 &rand);
	std::string checkWorldGenerator(std::string wayToFile);
	static void setWorldGenerator(std::string wayToFile);
};
class Energy
{
	UnderFunctions under;
	std::map<int, std::string>orbsTypes;
	int howManyOrbs;
public:
	unsigned int id;
	glm::vec3 position;

	Energy(Save &save, std::mt19937 &rand, glm::vec3 &energyPosition, std::string &login);
	Energy();
	~Energy();
	std::string changeEnergyToString(unsigned int id);
};
class WorldGenerator
{
private:
	float angle;

	ClockTimer clockTimer;
protected:
	int howManyObjects;
	UnderFunctions under;
public:
	std::map<int, Figures> objects;

	float xAngle;
	float yAngle;

	Energy *energy;
	glm::vec3 *positions;

	WorldGenerator(int howMany, std::mt19937 &rand, Save &save, std::string &login);
	WorldGenerator(int howMany, std::mt19937 &rand, Save &save, std::string &login, glm::vec3 position);
	WorldGenerator();
	~WorldGenerator();

	void drawWorld(GLint &textureSlot, int textureValue, GLint &transforms, Save &save);
	void elipseMoving();
};
class CustomWorldGenerator
{
	UnderFunctions under;
	WorldGenerator worldGenerator;
public:
	int howManyObjects;
	std::map<int, Figures> objects;
	glm::vec3 *positions;

	CustomWorldGenerator(int howMany, std::mt19937 &rand, Save &save, std::string &login);
	CustomWorldGenerator(int howMany, std::mt19937 &rand, Save &save, std::string &login, glm::vec3 position);
	CustomWorldGenerator();
	~CustomWorldGenerator();

	void drawWorld(GLint &textureSlot, int textureValue, GLint &transforms, Save &save);
	void sourceMoving(glm::vec3 &moveTo, int speed);
};