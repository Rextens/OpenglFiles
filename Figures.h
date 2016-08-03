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
#include "Vertices.h"
#include <vector>

#define LAST size() - 1

struct Slots
{
	Slots(Rendering &render);
	static Rendering render;
	static GLuint shaders;

	static GLint textureSlot;

	static GLint viewUniform;
	static GLint perspectiveUniform;
	static GLint light;
	static GLint transforms;
};

class Save
{
public:
	std::map<int, glm::vec3> position;

	std::map<int, std::map<int, std::string> > orbsBoard;
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

	template<class Type>
	void checkVector(std::vector<Type> &vector, std::string wayToFile, Vertices &vertices)
	{
		std::ifstream inputPositions(wayToFile);

		glm::vec3 positions(0.0f, 0.0f, 0.0f);
		while (inputPositions.good())
		{
			inputPositions >> positions.x;
			inputPositions >> positions.y;
			inputPositions >> positions.z;

			vector.push_back(Figures(vertices));
			vector[vector.LAST].setPosition(positions);
		}
	}

	template<class Type>
	void saveVector(std::vector<Type> &vector, std::string wayToFile)
	{
		std::ofstream outputPositions(wayToFile);

		for (unsigned int i = 0; i < vector.size(); ++i)
		{
			outputPositions << vector[i].position.x << " " << vector[i].position.y << " " << vector[i].position.z << "\n";
		}
	}

	template<class Type>
	void saveVector(std::vector<Type> &vector, std::string wayToFile, glm::vec3 &add)
	{
		std::ofstream outputPositions(wayToFile);

		for (unsigned int i = 0; i < vector.size(); ++i)
		{
			outputPositions << vector[i].position.x + add.x << " " << vector[i].position.y + add.y << " " << vector[i].position.z + add.z << "\n";
		}
	}
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
	Figures(Vertices &vertices);
	Figures(Vertices &vertices, Save &save);
	Figures();
	~Figures();

	void setPosition(glm::vec3 &newPosition);
	void setRotate(float angle, glm::vec3 &isActive);
	void setScale(glm::vec3 &scaling);
	void draw(int textureValue, Vertices &vertices);
	void draw(int textureValue, Save &save, Vertices &vertices);
	void take(GLFWwindow *window, GLint &transforms, glm::vec3 yourPosition);
	void moving(glm::vec3 moveValue);
	void movingTo(glm::vec3 &moveTo, float speed);
	void setPrivot(glm::vec3 privotPosition);

	std::vector<GLfloat>texture;

	GLuint vao = 0;

	glm::mat4 transform = glm::mat4(1.0f);
	glm::vec3 position = glm::vec3(0.0f, 1.0f, 0.0f);
	
	float angle;
	unsigned int nr = 0;
}; 
