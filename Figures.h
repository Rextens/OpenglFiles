#pragma once

#include <GL\glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <glfw3.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>

#include "Window.h"
#include "Rendering.h"

struct Orbs
{
	std::string firstAspect;
	std::string secondAspect;
	std::string thirdAspect;
};

class Save
{
public:
	std::map<int, glm::vec3>position;

	std::map<int, std::map<int, std::string> >orbsBoard;
	std::map<int, int> howMany;
	std::map<int, float> timers;
	std::map<int, std::map<int, float> > statistics;

	Save(std::string savePosition);
	void savePos(std::string wayToFile);
	void checkOrbs(std::string wayToFile);
	void saveOrbs(std::string wayToFile);
	void checkhowManyOrbs(std::string wayToFile);
	void saveHowManyOrbs(std::string wayToFile);
	void checkTimers(std::string wayToFile);
	void saveTimers(std::string wayToFile);
	void checkStatistics(std::string wayToFile);
	void saveStatistics(std::string wayToFile);
};
struct Repeatable
{
	glm::vec3 newPosition;
	glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);

	float x, z, difference;
};
class Figures
{
private:
	Rendering render;

	Repeatable repeatable;
	glm::vec3 privotPosition = glm::vec3(0.0f, 0.0f, 0.0f);
public:
	Figures(std::string wayToFile, std::string wayToFileTex);
	Figures(std::string wayToFile, std::string wayToFileTex, Save &save);
	Figures();
	~Figures();
	void setTransform(glm::vec3 &newPosition, float angle, glm::vec3 rotValue);
	void draw(GLint &textureSlot, int textureValue, GLint &transforms);
	void draw(GLint &textureSlot, int textureValue, GLint &transforms, Save &save);
	void take(GLFWwindow *window, GLint &transforms, glm::vec3 yourPosition);
	void moving(glm::vec3 moveValue, float angleValue, glm::vec3 rotValue);
	void movingTo(glm::vec3 &moveTo, float speed);
	void setPrivot(glm::vec3 privotPosition);

	std::vector<GLfloat>blackboard; 
	std::vector<GLfloat>texture;

	GLuint textureVbo = 0;
	GLuint vbo = 0;
	GLuint vao = 0;

	glm::mat4 transform;
	glm::mat4 rot;
	glm::vec3 position = glm::vec3(0.0f, 1.0f, 0.0f);
	
	float angle;
	unsigned int nr = 0;
}; 