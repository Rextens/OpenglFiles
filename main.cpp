#include "Figures.h"
#include "Rendering.h"
#include "Window.h"
#include "Timer.h"
#include "MouseAndKeyboard.h"
#include "Skybox.h"
#include "Game.h"
#include "Entities.h"
#include "Logining.h"
#include "LoadModels.h"
#include "World.h"
#include "Auxiliary.h"
#include "ClockTimer.h"
#include "LoadModels.h"

int main()
{
	Logining login;

	int what = -1;

	std::cout << "0. Zaloguj" << std::endl << "1. Zarejestruj";

	while (what != 0)
	{
		std::cin >> what;
		if (what == 0)
		{
			login.loadLogins("C:/Game/logins.txt");
		}
		else if (what == 1)
		{
			login.registry("C:/Game/logins.txt");
		}
	}
	if (login.logining)
	{
		Rendering render;
		Window window(800, 600, "", 4, !true, "C:/Game/Saves/" + login.loginNow + "/Save/camera/cameraPosition.txt");

		Skybox skybox(render);

		Timer time;
		MouseAndKeyboard MAK;
		Game game("C:/Game/Saves/" + login.loginNow + "/Save/Player/statistics.txt", login.loginNow);

		Save save("C:/Game/Saves/" + login.loginNow + "/Save/Objects/saveObjects.txt");
		save.checkhowManyOrbs("C:/Game/Saves/" + login.loginNow + "/Save/Objects/howManyOrbs.txt");
		save.checkOrbs("C:/Game/Saves/" + login.loginNow + "/Save/Objects/saveOrbs.txt");
		save.checkTimers("C:/Game/Saves/" + login.loginNow + "/Save/Timers/saveTimers.txt");
		save.checkStatistics("C:/Game/Saves/" + login.loginNow + "/Save/Statistics/statistics.txt");

		std::mt19937 rand((unsigned int)std::time(nullptr));

		Entities snail("C:/Game/Interface/hand.txt", "C:/Game/Blocks/floor/floorTexture.txt", save, 0.1f, 0.0f, 50.0f);
		snail.entitiesDefense = EntitiesDefense(1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

		GLuint shaders = render.loadShader("C:/Game/Shaders/vertexShader.glsl", "C:/Game/Shaders/fragmentShader.glsl");
		GLint texture_slot = glGetUniformLocation(shaders, "basic_texture");

		GLint viewUniform = glGetUniformLocation(shaders, "view_matrix");
		GLint perspectiveUniform = glGetUniformLocation(shaders, "perspective_matrix");
		GLint light = glGetUniformLocation(shaders, "ambientColor");
		GLint transforms = glGetUniformLocation(shaders, "transform");

		glActiveTexture(GL_TEXTURE0);
		render.loadTexture("C:/Game/Textures/Bricks.jpg");
		glActiveTexture(GL_TEXTURE1);
		render.loadTexture("C:/Game/Textures/Grass.jpg");

		game.setCamera(window, viewUniform, perspectiveUniform);

		glUseProgram(shaders);

		game.preFigures(save, login.loginNow, rand);

		render.deep();

		while (!glfwWindowShouldClose(window.window))
		{
			render.ClearColor(0.15f, 0.15f, 1.0f, 0.0f, window.window_width, window.window_height);

			game.attack(Entities::isAttacked, window);

			window.moving(game.lifeFunctions, game.moveSpeed);
			MAK.closeWindow(window);

			time.dayAndNight(light);

			game.setTime(window);
			game.sendCamera(window, render, viewUniform, perspectiveUniform);

			skybox.drawSkybox(transforms, texture_slot, window);

			game.setWorldPosition(texture_slot, transforms, save);
			game.die(10, glm::vec3(0.0f, 0.0f, 0.0f));

			snail.drawEntity(texture_slot, transforms, save);
			snail.aggresive(window.camera_position, 1);
			snail.attack(0.5f, 5.0f, 1.0f, game, window.camera_position, PHISICAL);
			snail.getDamage(window, game);

			render.ProcessWindowEvents(window.window);
		}

		save.savePos("C:/Game/Saves/" + login.loginNow + "/Save/Objects/saveObjects.txt");
		save.saveOrbs("C:/Game/Saves/" + login.loginNow + "/Save/Objects/saveOrbs.txt");
		save.saveHowManyOrbs("C:/Game/Saves/" + login.loginNow + "/Save/Objects/howManyOrbs.txt");
		save.saveTimers("C:/Game/Saves/" + login.loginNow + "/Save/Timers/saveTimers.txt");
		save.saveStatistics("C:/Game/Saves/" + login.loginNow + "/Save/Statistics/statistics.txt");

		UnderFunctions::setWorldGenerator("C:/Game/Saves/" + login.loginNow + "/Save/Objects/generateOrbs.txt");
		UnderFunctions::setWorldGenerator("C:/Game/Saves/" + login.loginNow + "/Save/Objects/generateWorld.txt");

		game.saveStatistics("C:/Game/Saves/" + login.loginNow + "/Save/Player/statistics.txt");
		window.saveCameraPosition("C:/Game/Saves/" + login.loginNow + "/Save/camera/cameraPosition.txt");
		render.Terminate(window.window);
	}
	return 0;
}