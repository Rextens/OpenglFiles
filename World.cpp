#include "World.h"

WorldGenerator::WorldGenerator(int howMany, std::mt19937 &rand, Save &save, std::string &login)
{
	howManyObjects = howMany;
	positions = new glm::vec3[howMany];
	energy = new Energy[howMany];

	for (unsigned int i = 0; i < howMany; i++)
	{
		positions[i] = under.randomPosition(rand);
		objects[i] = Figures("C:/Game/Blocks/brick/brick.txt", "C:/Game/Blocks/brick/brickTexture.txt", save);
		if (under.checkWorldGenerator("C:/Game/Saves/" + login + "/Save/Objects/generateWorld.txt") == "0")
		{
			objects[i].setTransform(positions[i], 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		energy[i] = Energy(save, rand, objects[i].position, login);
	}
}
WorldGenerator::WorldGenerator(int howMany, std::mt19937 &rand, Save &save, std::string &login, glm::vec3 position)
{
	howManyObjects = howMany;
	positions = new glm::vec3[howMany];
	energy = new Energy[howMany];

	for (unsigned int i = 0; i < howMany; i++)
	{
		positions[i] = under.randomPosition(rand) + position;
		objects[i] = Figures("C:/Game/Blocks/brick/brick.txt", "C:/Game/Blocks/brick/brickTexture.txt", save);
		if (under.checkWorldGenerator("C:/Game/Saves/" + login + "/Save/Objects/generateWorld.txt") == "0")
		{
			objects[i].setTransform(positions[i], 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		energy[i] = Energy(save, rand, objects[i].position, login);
	}
}
WorldGenerator::WorldGenerator()
{
}
WorldGenerator::~WorldGenerator()
{
}
void WorldGenerator::drawWorld(GLint &textureSlot, int textureValue, GLint &transforms, Save &save)
{
	for (unsigned int i = 0; i < howManyObjects; i++)
	{
		objects[i].draw(textureSlot, 0, transforms, save);
	}
}
void WorldGenerator::elipseMoving()
{
	if (clockTimer.getTimeAsSeconds() > 0.01)
	{
		angle += 1.0;

		xAngle = 1.0f * cos(angle * 3.14 / 180.0);
		yAngle = 1.0f * sin(angle * 3.14 / 180.0);

		clockTimer.restart();
	}
}

UnderFunctions::UnderFunctions()
{

}
UnderFunctions::~UnderFunctions()
{

}
glm::vec3 UnderFunctions::randomPosition(std::mt19937 &rand)
{
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

	std::uniform_real_distribution<float>positionX(-10, 10);
	position.x = positionX(rand);

	std::uniform_real_distribution<float>positionZ(-10, 10);
	position.z = positionZ(rand);

	return position;
}
glm::vec3 UnderFunctions::randomPosition(std::mt19937 &rand, glm::vec2 &bonusRand)
{
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

	std::uniform_real_distribution<float>positionX(-bonusRand.x, bonusRand.y);
	position.x = positionX(rand);

	std::uniform_real_distribution<float>positionZ(-bonusRand.x, bonusRand.y);
	position.z = positionZ(rand);

	return position;
}
int UnderFunctions::type(int min, int max, std::mt19937 &rand)
{
	std::uniform_real_distribution<float>type((float)min, (float)max + 1);

	return (int)type(rand);
}
std::string UnderFunctions::checkWorldGenerator(std::string wayToFile)
{
	std::ifstream input(wayToFile);

	if (!input)
	{
		std::cout << "Cannot check world generator type" << std::endl;

		system("pause");

		exit(1);
	}
	std::string number;

	std::getline(input, number);

	return number;
}
void UnderFunctions::setWorldGenerator(std::string wayToFile)
{
	std::ofstream output(wayToFile);

	output << "1";

	output.close();
}

Energy::Energy(Save &save, std::mt19937 &rand, glm::vec3 &energyPosition, std::string &login)
{
	static unsigned int number;

	id = number;

	position = energyPosition;

	howManyOrbs = save.howMany[id];

	for (unsigned int i = 0; i < howManyOrbs; i++)
	{
		orbsTypes[i] = save.orbsBoard[id][i];
	}

	if (under.checkWorldGenerator("C:/Game/Saves/" + login + "/Save/Objects/generateOrbs.txt") == "0")
	{
		howManyOrbs = under.type(1, 3, rand);
		save.howMany[id] = howManyOrbs;

		for (unsigned int i = 0; i < howManyOrbs; i++)
		{
			orbsTypes[i] = changeEnergyToString(under.type(0, 11, rand));
			save.orbsBoard[id][i] = orbsTypes[i];
		}
	}
	number++;
}
Energy::Energy()
{

}
Energy::~Energy()
{

}
std::string Energy::changeEnergyToString(unsigned int id)
{
	if (id == 0)
	{
		return "fire";
	}
	else if (id == 1)
	{
		return "earth";
	}
	else if (id == 2)
	{
		return "aer";
	}
	else if (id == 3)
	{
		return "fire";
	}
	else if (id == 4)
	{
		return "ice";
	}
	else if (id == 5)
	{
		return "clearEnergy";
	}
	else if (id == 6)
	{
		return "darkEnergy";
	}
	else if (id == 7)
	{
		return "stone";
	}
	else if (id == 8)
	{
		return "rage";
	}
	else if (id == 9)
	{
		return "life";
	}
	else if (id == 10)
	{
		return "daed";
	}
	else if (id == 11)
	{
		return "spirit";
	}
	else if (id == 12)
	{
		return "motion";
	}
	else if(id == 13)
	{
		return "electricy";
	}
}

CustomWorldGenerator::CustomWorldGenerator(int howMany, std::mt19937 &rand, Save &save, std::string &login)
{
	howManyObjects = howMany;
	positions = new glm::vec3[howMany];

	for (unsigned int i = 0; i < howMany; i++)
	{
		positions[i] = under.randomPosition(rand);
		objects[i] = Figures("C:/Game/Blocks/brick/brick.txt", "C:/Game/Blocks/brick/brickTexture.txt", save);
		if (under.checkWorldGenerator("C:/Game/Saves/" + login + "/Save/Objects/generateWorld.txt") == "0")
		{
			objects[i].setTransform(positions[i], 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		}
	}
}
CustomWorldGenerator::CustomWorldGenerator(int howMany, std::mt19937 &rand, Save &save, std::string &login, glm::vec3 position)
{
	howManyObjects = howMany;
	positions = new glm::vec3[howMany];

	for (unsigned int i = 0; i < howMany; i++)
	{
		positions[i] = under.randomPosition(rand) + position;
		objects[i] = Figures("C:/Game/Blocks/brick/brick.txt", "C:/Game/Blocks/brick/brickTexture.txt", save);
		if (under.checkWorldGenerator("C:/Game/Saves/" + login + "/Save/Objects/generateWorld.txt") == "0")
		{
			objects[i].setTransform(positions[i], 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		}
	}
}
CustomWorldGenerator::CustomWorldGenerator()
{

}
CustomWorldGenerator::~CustomWorldGenerator()
{

}
void CustomWorldGenerator::drawWorld(GLint &textureSlot, int textureValue, GLint &transforms, Save &save)
{
	for (unsigned int i = 0; i < howManyObjects; i++)
	{
		objects[i].draw(textureSlot, 0, transforms, save);
	}
}
void CustomWorldGenerator::sourceMoving(glm::vec3 &moveTo, int speed)
{
	for (unsigned int i = 0; i < howManyObjects; i++)
	{
		objects[i].movingTo(moveTo, speed);

		if (Auxiliary::getDistance(objects[i].position, moveTo, 0.1f))
		{
			objects[i].setTransform(positions[i], 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		}
	}
}