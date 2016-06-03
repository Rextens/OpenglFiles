#pragma once

#include <GL\glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <vector>

class Window
{
private:
	std::vector<bool>boolBoard;
public:
	static double horizontal_angle;
	static double vertical_angle;

	static glm::vec3 camera_position;
    static glm::vec3 camera_direction;
	static glm::vec3 camera_right;
	static glm::vec3 camera_up;
	static glm::vec3 camera_jump;
	static glm::mat4 view_matrix;

	glm::mat4 ortho;

	static double actual_time;
	static double previous_time;

	static glm::mat4 perspective;


	static float P1;
	static float P2;
	static float FOV;
	static float aspect;

	static int window_width;
	static int window_height;

	static GLFWwindow *window;

	float cameraPosition[3];
	float cameraDirection[3];

	Window(int width, int height, std::string name, int samples, bool fullscreen, std::string wayToFilePos);
	Window();
	static double getDeltaTime();
	static void cursorMove(GLFWwindow* window, double x_cursor_pos, double y_cursor_pos);
	static void windowSizeCallback(GLFWwindow* /*window*/, int width, int height);
	static void saveCameraPosition(std::string wayToFilePos);
	static void moving(bool &lifeFunctions, float &moveSpeed);
	void setOrtho();
};


