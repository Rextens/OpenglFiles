#include "Skybox.h"



Skybox::Skybox(Rendering &render)
{
	glActiveTexture(GL_TEXTURE2);
	render.loadTexture("C:/Game/Skybox/top.jpg");
	glActiveTexture(GL_TEXTURE3);
	render.loadTexture("C:/Game/Skybox/bot.jpg");
	glActiveTexture(GL_TEXTURE4);
	render.loadTexture("C:/Game/Skybox/right.jpg");
	glActiveTexture(GL_TEXTURE5);
	render.loadTexture("C:/Game/Skybox/left.jpg");
	glActiveTexture(GL_TEXTURE6);
	render.loadTexture("C:/Game/Skybox/front.jpg");
	glActiveTexture(GL_TEXTURE7);
	render.loadTexture("C:/Game/Skybox/back.jpg");
}


Skybox::~Skybox()
{
}

void Skybox::drawSkybox(GLint &transforms, GLint &textureSlot, Window &window)
{
	figureWallTop.setTransform(glm::vec3(window.camera_position.x, window.camera_position.y, window.camera_position.z - 0.5), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	figureWallTop.draw(textureSlot, 2, transforms);

	figureWallBot.setTransform(glm::vec3(window.camera_position.x, window.camera_position.y, window.camera_position.z - 0.5), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	figureWallBot.draw(textureSlot, 3, transforms);

	figureWallRight.setTransform(glm::vec3(window.camera_position.x, window.camera_position.y, window.camera_position.z - 0.5), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	figureWallRight.draw(textureSlot, 7, transforms);

	figureWallLeft.setTransform(glm::vec3(window.camera_position.x, window.camera_position.y, window.camera_position.z - 0.5), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	figureWallLeft.draw(textureSlot, 5, transforms);

	figureWallFront.setTransform(glm::vec3(window.camera_position.x, window.camera_position.y, window.camera_position.z - 0.5), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	figureWallFront.draw(textureSlot, 6, transforms);

	figureWallBack.setTransform(glm::vec3(window.camera_position.x, window.camera_position.y, window.camera_position.z - 0.5), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	figureWallBack.draw(textureSlot, 4, transforms);
}