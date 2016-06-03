#pragma once

#include <GL\glew.h>
#include "Figures.h"
#include "Window.h"
#include "Rendering.h"

class Skybox
{
private:
	Figures figureWallTop = Figures("C:/Game/Blocks/skybox/top.txt", "C:/Game/Blocks/skybox/topTexture.txt");
	Figures figureWallBot = Figures("C:/Game/Blocks/skybox/bot.txt", "C:/Game/Blocks/skybox/botTexture.txt");
	Figures figureWallRight = Figures("C:/Game/Blocks/skybox/right.txt", "C:/Game/Blocks/skybox/rightTexture.txt");
	Figures figureWallLeft = Figures("C:/Game/Blocks/skybox/left.txt", "C:/Game/Blocks/skybox/leftTexture.txt");
	Figures figureWallFront = Figures("C:/Game/Blocks/skybox/front.txt", "C:/Game/Blocks/skybox/frontTexture.txt");
	Figures figureWallBack = Figures("C:/Game/Blocks/skybox/back.txt", "C:/Game/Blocks/skybox/backTexture.txt");
public:
	Skybox(Rendering &render);
	~Skybox();
	void drawSkybox(GLint &transforms, GLint &textureSlot, Window &window);
};

