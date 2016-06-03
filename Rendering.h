#pragma once

#include <GL\glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <iostream>
#include <FreeImage.h>
#include <vector>

struct Texture
{
	BYTE *bits;
	FIBITMAP *imagePtr;
	int width;
	int height;
};

class Rendering
{
public:
	Rendering();

	std::vector<GLfloat>skyboxBlackboard;

	GLint loadShader(std::string wayToVertexShader, std::string wayToFragmentShader);
	int loadTexture(std::string wayToTexture);
	int loadTexture(std::string wayToFile, GLuint &handle);
	int loadTexture(std::string wayToFile, Texture &texture);
	void glewInitialization();
	void glfwInitialization();
	void deep();
	void ProcessWindowEvents(GLFWwindow *window);
	void Terminate(GLFWwindow *window);
	void ClearColor(float r, float g, float b, float alpha, int windowWidth, int windowHeight);
	int findUniform(GLuint shader_program, std::string uniform_name);
	void setUniform(GLint uniform_handle, GLint value);
	void setUniform(GLint uniform_handle, const glm::mat4 &matrix);
};

