#pragma once

#include "Figures.h"
#include "Game.h"
#include "ClockTimer.h"
#include "Auxiliary.h"

#include <ctime>
#include <random>

#define PHISICAL "phisical"
#define POISON "poison"
#define FIRE "fire"
#define MAGIC "magic"
#define ICE "ice"

struct EntitiesStatistics
{
	float maxHp = 0;
	float hp = 50;
	float damage = 0;
	float attackSpeed = 0;
	float speed = 0;
	float hpRegeneration = 0;
};
struct EntitiesDefense
{
	EntitiesDefense(float armor, float fireArmor, float iceArmor, float magicArmor, float poisonArmor);
	EntitiesDefense();

	float armor = 0;
	float fireArmor = 0;
	float poisonArmor = 0;
	float iceArmor = 0;
	float magicArmor = 0;
};
struct EntitiesValues
{
	ClockTimer moveTimer;

	float xMove;
	float zMove;

	std::mt19937 rand;
	float moveSpeed = 0;

	ClockTimer clock;
	ClockTimer attackSpeedTimer;

	float cooldawn;

	bool isAgressive = false;
};
class Entities
{
private:
	EntitiesValues entities;
	ClockTimer attackSpeed;

public:
	static bool isAttacked;
	unsigned int id;

	EntitiesStatistics entitiesStatistict;
	EntitiesDefense entitiesDefense;

	Entities(std::string wayToMesh, std::string wayToTextureMesh, Save &save, float speed, float hpRegen, float maxHp);
	~Entities();

	void drawEntity(GLint &textureSlot, GLint &transforms, Save &save);
	void attack(float distance, float damage, float attackSpeed, Game &game, glm::vec3 &playerPos, std::string damageType);
	void aggresive(glm::vec3 &playerPos, float distancee);
	void getDamage(Window &window, Game &game);
	float damage(Game &game, std::string damageType);

	Figures entity;
};

