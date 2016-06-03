#include "Entities.h"

bool Entities::isAttacked = false;

Entities::Entities(std::string wayToMesh, std::string wayToTextureMesh, Save &save, float speed, float hpRegen, float maxHp)
{
	static unsigned int nr = 0;
	id = nr;

	entity = Figures(wayToMesh, wayToTextureMesh, save);
	entity.setTransform(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	entitiesStatistict.hp = maxHp;

	entities.rand = std::mt19937((unsigned int)std::time(nullptr));
	std::uniform_real_distribution<float>distX(-10, 10);
	entities.xMove = distX(entities.rand);

	std::uniform_real_distribution<float>distZ(-10, 10);
	entities.zMove = distZ(entities.rand);

	std::uniform_real_distribution<float>distC(0, 10);
	entities.cooldawn = distC(entities.rand);

	entitiesStatistict.hp = save.statistics[id][0];

	entitiesStatistict.speed = speed;
	entitiesStatistict.hpRegeneration = hpRegen;
	entitiesStatistict.maxHp = maxHp;

	nr++;

	std::cout << entitiesStatistict.hp;
}
Entities::~Entities()
{

}
void Entities::drawEntity(GLint &textureSlot, GLint &transforms, Save &save)
{
	static ClockTimer hpRegen;
	if (entitiesStatistict.hp > 0)
	{
		if (!entities.isAgressive)
		{
			if (entities.clock.getTimeAsSeconds() > entities.cooldawn)
			{
				entities.rand = std::mt19937((unsigned int)std::time(nullptr));
				std::uniform_real_distribution<float>distX(-10, 10);
				entities.xMove = distX(entities.rand);

				std::uniform_real_distribution<float>distZ(-10, 10);
				entities.zMove = distZ(entities.rand);

				std::uniform_real_distribution<float>distC(0, 10);
				entities.cooldawn = distC(entities.rand);

				entities.clock.restart();
			}

			entity.movingTo(glm::vec3(entities.xMove, 0.0f, entities.zMove), entitiesStatistict.speed);
		}
		if (hpRegen.getTimeAsSeconds() >= 1.0f && entitiesStatistict.hp < entitiesStatistict.maxHp)
		{
			entitiesStatistict.hp += entitiesStatistict.hpRegeneration;
			if (entitiesStatistict.hp > entitiesStatistict.maxHp)
			{
				entitiesStatistict.hp = entitiesStatistict.maxHp;
			}
		}
		entity.draw(textureSlot, 0, transforms, save);
	}

	save.statistics[id][0] = entitiesStatistict.hp;
}
void Entities::attack(float distance, float damage, float attackSpeed, Game &game, glm::vec3 &playerPos, std::string damageType)
{
	entitiesStatistict.damage = damage;
	entitiesStatistict.attackSpeed = attackSpeed;

	if (Auxiliary::getDistance(entity.position, playerPos, distance))
	{
		if (entities.attackSpeedTimer.getTimeAsSeconds() >= entitiesStatistict.attackSpeed)
		{
			game.life -= game.damages(entitiesStatistict.damage, damageType);

			entities.attackSpeedTimer.restart();
		}
	}
}
void Entities::aggresive(glm::vec3 &playerPos, float distance)
{
	if (Auxiliary::getDistance(playerPos, entity.position, distance))
	{
		entities.isAgressive = true;
		
		entity.movingTo(playerPos, entitiesStatistict.speed);
	}
	else if (!Auxiliary::getDistance(playerPos, entity.position, distance))
	{
		entities.isAgressive = false;
	}
}
void Entities::getDamage(Window &window, Game &game)
{
	if (isAttacked && Auxiliary::getDistance(window.camera_position, entity.position, 0.5))
	{
		entitiesStatistict.hp -= damage(game, PHISICAL);
	}
}
float Entities::damage(Game &game, std::string damageType)
{
	float returnedDamage = 0;
	if (damageType == "phisical")
	{
		returnedDamage = game.damage - entitiesDefense.armor / 2.0f;

		if (returnedDamage < 0)
		{
			return 0;
		}
		else
		{
			return returnedDamage;
		}
	}
	else if (damageType == "poison")
	{
		returnedDamage = game.damage - entitiesDefense.poisonArmor / 1.5f;

		if (returnedDamage < 0)
		{
			return 0;
		}
		else
		{
			return returnedDamage;
		}
	}
	else if (damageType == "fire")
	{
		returnedDamage = game.damage - entitiesDefense.fireArmor / 2.0f;

		if (returnedDamage < 0)
		{
			return 0;
		}
		else
		{
			return returnedDamage;
		}
	}
	else if (damageType == "magic")
	{
		returnedDamage = game.damage - entitiesDefense.magicArmor / 3.0f;

		if (returnedDamage < 0)
		{
			return 0;
		}
		else
		{
			return returnedDamage;
		}
	}
	else if (damageType == "ice")
	{
		returnedDamage = game.damage - entitiesDefense.iceArmor / 2.0f;

		if (returnedDamage < 0)
		{
			return 0;
		}
		else
		{
			return returnedDamage;
		}
	}
	else
	{
		damageType = "phisical";
	}
}

EntitiesDefense::EntitiesDefense(float armor, float fireArmor, float iceArmor, float magicArmor, float poisonArmor)
{
	this->armor = armor;
	this->fireArmor = fireArmor;
	this->iceArmor = iceArmor;
	this->magicArmor = magicArmor;
	this->poisonArmor = poisonArmor;
}
EntitiesDefense::EntitiesDefense()
{
}







