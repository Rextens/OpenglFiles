#include "Game.h"



Game::Game(std::string wayToFIle, std::string &login)
{
	std::ifstream loadClass("C:/Game/Saves/" + login + "/Save/Player/ChampionClass.txt");

	if (!loadClass)
	{
		std::cout << "Can't load champion class" << std::endl;
		return;
	}

	loadClass >> championClass;
	loadClass.close();

	if (championClass == championClasses::Archer)
	{
		life = 34;
		maxLife = 34;
		damage = 3;
		moveSpeed = 7;
		attackSpeed = 2;

		poisonArmor = 7;
	}
	else if (championClass == championClasses::Warrior)
	{
		life = 76;
		maxLife = 76;
		damage = 2;
		moveSpeed = 3;
		attackSpeed = 3;

		iceArmor = 8;
	}	
	else if (championClass == championClasses::Wizard)
	{
		life = 37;
		maxLife = 37;
		damage = 6;
		moveSpeed = 4;
		attackSpeed = 3;

		iceArmor = 2;
		poisonArmor = 3;
		magicArmor = 5;
		fireArmor = 1;
	}
	if (championClass == -1)
	{
		std::cout << "Unknow champion class" << std::endl;
		return;
	}

	std::ifstream input(wayToFIle);

	std::vector<float> statistics;

	while (!input.eof())
	{
		float temp;
		input >> temp;
		statistics.push_back(temp);
	}

	life = statistics[0];
	concetration = statistics[1];
	rage = statistics[2];

	energy.darkEnergy = statistics[3];
	energy.electricyEnergy = statistics[4];
	energy.fireEnergy = statistics[5];
	energy.iceEnegry = statistics[6];
	energy.lightEnergy = statistics[7];
	energy.stoneEnergy = statistics[8];
	energy.rageEnergy = statistics[9];
	energy.lifeEnergy = statistics[10];
	energy.deadEnergy = statistics[11];
	energy.spiritEnergy = statistics[12];
	energy.motionEnergy = statistics[13];
	energy.earthEnergy = statistics[14];
	energy.aerEnergy = statistics[15];
	energy.cleanEnergy = statistics[16];

	input.close();
}
Game::~Game()
{

}
void Game::die(float time, glm::vec3 &startPosition)
{
	if (life >= 0)
	{
		respawning.restart();

		lifeFunctions = true;
	}
	else
	{
		if (respawning.getTimeAsSeconds() >= time)
		{
			life = maxLife;
			startPosition.x = 0;
			startPosition.y = 0;
			startPosition.z = 0;
		}
		lifeFunctions = false;
	}
}
void Game::preFigures(Save &save, std::string &login, std::mt19937 &rand)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			bonusPosition[i][j] = under.randomPosition(rand, glm::vec2(-10, 10));
			figures[i][j] = Figures("C:/Game/Blocks/floor/floor.txt", "C:/Game/Blocks/floor/floorTexture.txt");
			worldGen[i][j] = WorldGenerator(20, rand, save, login, glm::vec3(i * 20, 0.75f, j * 20));
			figures[i][j].setTransform(glm::vec3(i * 40.0f, 0.0f, j * 40.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
			customWorldGen[i][j] = CustomWorldGenerator(20, rand, save, login, glm::vec3(i * 40 + bonusPosition[i][j].x, 0.0f, j * 40 + bonusPosition[i][j].z));
		}
	}
}
void Game::setWorldPosition(GLint &textureSlot, GLint &transforms, Save &save)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			figures[i][j].draw(textureSlot, 1, transforms);
			worldGen[i][j].drawWorld(textureSlot, 0, transforms, save);
			customWorldGen[i][j].drawWorld(textureSlot, 1, transforms, save);
			customWorldGen[i][j].sourceMoving(figures[i][j].position + bonusPosition[i][j], 1.0f);		
		}
	}
}
float Game::damages(float damageSize, std::string damageType)
{
	float returnedDamage = 0;
	if (damageType == "phisical")
	{
		returnedDamage = damageSize - armor / 2.0f;

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
		returnedDamage = damageSize - poisonArmor / 1.5f;

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
		returnedDamage = damageSize - fireArmor / 2.0f;
	
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
		returnedDamage = damageSize - magicArmor / 3.0f;
	
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
		returnedDamage = damageSize - iceArmor / 2.0f;
	
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
void Game::saveStatistics(std::string wayToFile)
{
	std::ofstream save(wayToFile);
	save << life << std::endl;
	save << concetration << std::endl;
	save << rage << std::endl;

	save << energy.darkEnergy << std::endl;
	save << energy.electricyEnergy << std::endl;
	save << energy.fireEnergy << std::endl;
	save << energy.iceEnegry << std::endl;
	save << energy.lightEnergy << std::endl;
	save << energy.stoneEnergy << std::endl;
	save << energy.rageEnergy << std::endl;
	save << energy.lifeEnergy << std::endl;
	save << energy.deadEnergy << std::endl;
	save << energy.spiritEnergy << std::endl;
	save << energy.motionEnergy << std::endl;
	save << energy.earthEnergy << std::endl;
	save << energy.aerEnergy << std::endl;
	save << energy.cleanEnergy << std::endl;

	save.close();
}
void Game::attack(bool isAttacked, Window &window)
{
	if (glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_LEFT) && AttackSpeed.getTimeAsSeconds() > attackSpeed)
	{
		isAttacked = true;

		AttackSpeed.restart();
	}
	isAttacked = false;
}

void Game::setCamera(Window &window, GLint &viewUniform, GLint &perspectiveUniform)
{
	window.camera_up = window.camera_right * window.camera_direction;
	window.view_matrix = glm::lookAt(window.camera_position, window.camera_position + window.camera_direction, window.camera_up);

	// Ustawienie perspektywy
	float P1 = 0.1f;
	float P2 = 100.0f;
	float FOV = 67.0f;
	float aspect = float(window.window_width) / float(window.window_height);

	window.perspective = glm::perspective(glm::radians(FOV), aspect, P1, P2);

	// Wyslanie perspektywy i pozycji kamery do programu shadera
	glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(window.view_matrix));
	glUniformMatrix4fv(perspectiveUniform, 1, GL_FALSE, glm::value_ptr(window.perspective));
}
void Game::sendCamera(Window &window, Rendering &render, GLint &view, GLint &perspective)
{
	render.setUniform(view, window.view_matrix);
	render.setUniform(perspective, window.perspective);
}
void Game::setTime(Window &window)
{
	window.previous_time = window.actual_time;
	window.actual_time = glfwGetTime();
}