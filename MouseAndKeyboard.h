#pragma once

#include <GL/glew.h>
#include "Auxiliary.h"
#include <iostream>
#include <glfw3.h>
#include <map>
#include <glm.hpp>

class MouseAndKeyboard
{
private:
	std::map<int, int> keyBoard;
	std::map<int, int> buttonBoard;

	std::map<int, bool> keyboardFlags;
	std::map<int, bool> mouseFlags;

	std::string sentence = "";
	std::string sentence2 = "";

	std::string numberSentence = "";
	std::string numberSentence2 = "";
public:
	MouseAndKeyboard();
	~MouseAndKeyboard();
	bool oneKeyPressed(GLFWwindow *window, int key);
	bool oneButtonPressed(GLFWwindow *window, int key);
	bool permaKeyPressed(GLFWwindow *window, int key);
	bool permaButtonPressed(GLFWwindow *window, int key);
	void closeWindow(GLFWwindow *window);
	std::string getKeybord(GLFWwindow *window);
	int getNumber(GLFWwindow *window);
	bool mouseCollision(glm::vec3 &opposite, float &size);
};

