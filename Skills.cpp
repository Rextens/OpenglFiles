#include "Skills.h"



Skills::Skills()
{
}


Skills::~Skills()
{
}
void Skills::dictionary(Window &window, Game &game)
{
	for (unsigned short int i = 0; i < abilities.size(); i++)
	{
		static unsigned int abilityStreng = 0;
		if (abilities[nr][i] == "lopi")
		{
			glm::vec3 push;

			push = window.camera_position + window.camera_direction;

			if (glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_LEFT) && loader.getTimeAsSeconds() > 0.1 && game.energy.motionEnergy > 0 && !isActiveated.book)
			{
				abilityStreng++;

				pushed = true;

				game.energy.motionEnergy -= 1;

				loader.restart();
			}
			else if (!glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_LEFT) && pushed)
			{
				window.camera_position = glm::vec3(push.x, push.y, push.z) + glm::vec3(window.camera_direction.x * abilityStreng, window.camera_direction.y * abilityStreng, window.camera_direction.z * abilityStreng);

				abilityStreng = 0;

				pushed = false;
			}
		}
		else if (abilities[nr][i] == "seris")
		{
			if (glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_LEFT) && loader.getTimeAsSeconds() > 0.1 && game.energy.lifeEnergy > 0 && !isActiveated.book)
			{
				pushed = true;

				abilityStreng++;
	
				loader.restart();
			}
			else if (!glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_LEFT) && pushed)
			{
				abilityStreng = 0;

				pushed = false;
			}
		}
	}
}
void Skills::sentence(Window &window, MouseAndKeyboard &MAK)
{
	static bool isActivate = false;
	if (glfwGetKey(window.window, GLFW_KEY_B))
	{
		isActivate = !isActivate;
		isActiveated.book = !isActiveated.book;
	}
	if (isActivate)
	{
		std::vector<std::string>word;

		ability = MAK.getKeybord(window);
		if (MAK.oneKeyPressed(window, GLFW_KEY_ENTER))
		{
			word.push_back(ability);
		}
		else if (MAK.oneKeyPressed(window, GLFW_KEY_ENTER) && MAK.oneKeyPressed(window, GLFW_KEY_LEFT_CONTROL))
		{
			abilities.push_back(word);
		}
	}
}
