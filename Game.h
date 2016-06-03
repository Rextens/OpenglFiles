#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <glm.hpp>

#include "Figures.h"
#include "World.h"

#define PHISICAL "phisical"
#define POISON "poison"
#define FIRE "fire"
#define MAGIC "magic"
#define ICE "ice"

struct PlayerEnergy
{
	float fireEnergy = 0;
	float iceEnegry = 0;
	float electricyEnergy = 0;
	float darkEnergy = 0;
	float lightEnergy = 0;
	float stoneEnergy = 0;
	float rageEnergy = 0;
	float lifeEnergy = 0;
	float deadEnergy = 0;
	float spiritEnergy = 0;
	float motionEnergy = 0;
	float earthEnergy = 0;
	float aerEnergy = 0;
	float cleanEnergy = 0;
};
class Game
{
private:
	enum championClasses {Archer, Warrior, Wizard};
	int championClass = -1;

	ClockTimer respawning;

	Figures figures[10][10];
	std::map<int, std::map<int, glm::vec3> > bonusPosition;
	UnderFunctions under;

	ClockTimer AttackSpeed;
public:
	WorldGenerator worldGen[10][10];
	CustomWorldGenerator customWorldGen[10][10];

	float armor = 0;
	float fireArmor = 0;
	float poisonArmor = 0;
	float iceArmor = 0;
	float magicArmor = 0;

	double life = 0; 

	PlayerEnergy energy;

	double concetration = 0;
	double rage = 0;

	double maxLife = 0.0;
	double damage = 0.0;
	float moveSpeed = 0.0;
	float attackSpeed = 0.0;

	bool lifeFunctions = true;

	std::vector<Figures> buildVector;

	Game(std::string wayToFile, std::string &login);
	~Game();

	void die(float time, glm::vec3 &newPosition);
	void setWorldPosition(GLint &textureSlot, GLint &transforms, Save &save);
	float damages(float damageSize, std::string damageType);
	void saveStatistics(std::string wayToFile);
	void preFigures(Save &save, std::string &login, std::mt19937 &rand);
	void attack(bool isAttacked, Window &window);

	void setCamera(Window &window, GLint &viewUniform, GLint &perspectiveUniform);
	void sendCamera(Window &moving, Rendering &render, GLint &view, GLint &perspective);
	void setTime(Window &window);
};

