#include "Window.h"

int Window::window_width = 0;
int Window::window_height = 0;

double Window::horizontal_angle = 0;
double Window::vertical_angle = 0;
double Window::actual_time = 0;
double Window::previous_time = 0;

float Window::P1 = 0.1f;
float Window::P2 = 150.0f;
float Window::FOV = 67.0f;
float Window::aspect = float(window_width) / float(window_height);

GLFWwindow *Window::window;

glm::vec3 Window::camera_position(0.0, 0.0, 2.0);
glm::vec3 Window::camera_direction(0.0, 0.0, -1.0);
glm::vec3 Window::camera_right(1.0, 0.0, 0.0);
glm::vec3 Window::camera_jump(0.0, 1.0, 0.0);
glm::vec3 Window::camera_up(0.0, 0.0, 0.0);

glm::mat4 Window::view_matrix(0.0);
glm::mat4 Window::perspective(0.0);

double Window::getDeltaTime()
{
	return actual_time - previous_time;
}
Window::Window(int width, int height, std::string name, int samples, bool fullscreen, std::string wayToFilePos)
{
	int tmp = 0;
	std::ifstream loadCameraPos(wayToFilePos);

	if (!loadCameraPos)
	{
		std::cout << "Cannot open file with camera position" << std::endl;
	}

	while (!loadCameraPos.eof())
	{
		loadCameraPos >> cameraPosition[tmp++];
	}

	loadCameraPos.close();

	camera_position.x = cameraPosition[0];
	camera_position.y = cameraPosition[1];
	camera_position.z = cameraPosition[2];

	if (!glfwInit())
	{
		std::cout << "GLFW initialization error." << std::endl;
		return;
	}

	glfwWindowHint(GLFW_SAMPLES, samples);

	if (fullscreen)
	{
		const GLFWvidmode* video_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		window_width = video_mode->width;
		window_height = video_mode->height;
		window = glfwCreateWindow(window_width, window_height, name.c_str(), glfwGetPrimaryMonitor(), NULL);
	}
	else
	{
		window_width = width;
		window_height = height;
		window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
	}

	if (!window)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW initialization error." << std::endl;
		return;
	}

	glfwSetCursorPosCallback(window, cursorMove);
	glfwSetWindowSizeCallback(window, windowSizeCallback);

	camera_position.y = 0.75;
}
Window::Window()
{

}
void Window::cursorMove(GLFWwindow* window, double x_cursor_pos, double y_cursor_pos)
{
	glfwSetCursorPos(window, 400, 300);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	float mouse_speed = 0.5f;
	
	horizontal_angle += mouse_speed * (float)getDeltaTime() * float(400 - x_cursor_pos);
	vertical_angle += mouse_speed * (float)getDeltaTime() * float(300 - y_cursor_pos);

	if (vertical_angle < -1.57)
	{
		vertical_angle = -1.57;
	}
	else if (vertical_angle > 1.57)
	{
		vertical_angle = 1.57;
	}
	
	camera_direction = glm::vec3(cos(vertical_angle) * sin(horizontal_angle), sin(vertical_angle), cos(vertical_angle) * cos(horizontal_angle));
	camera_right = glm::vec3(-cos(horizontal_angle), 0, sin(horizontal_angle));
	camera_up = glm::cross(camera_right, camera_direction);

	view_matrix = glm::lookAt(camera_position, camera_position + camera_direction, camera_up);
}
void Window::windowSizeCallback(GLFWwindow* /*window*/, int width, int height)
{
	window_width = width;
	window_height = height;
}
void Window::saveCameraPosition(std::string wayToFilePos)
{
	std::ofstream out;

	out.open(wayToFilePos);

		out << camera_position.x << std::endl;
		out << camera_position.y << std::endl;
		out << camera_position.z << std::endl;

	out.close();
}
void Window::moving(bool &lifeFunctions, float &moveSpeed)
{
	static bool fall = false;
	if (lifeFunctions)
	{
		if (glfwGetKey(window, GLFW_KEY_W))
		{
			camera_position.x += camera_direction.x * (float)getDeltaTime() * moveSpeed;
			camera_position.z += camera_direction.z * (float)getDeltaTime() * moveSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_S))
		{
			camera_position.x -= camera_direction.x * (float)getDeltaTime() * moveSpeed;
			camera_position.z -= camera_direction.z * (float)getDeltaTime() * moveSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_A))
		{
			camera_position -= camera_right * (float)getDeltaTime() * moveSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_D))
		{
			camera_position += camera_right * (float)getDeltaTime() * moveSpeed;
		}
		if (MAK.oneKeyPressed(window, GLFW_KEY_SPACE))
		{
			fall = true;
		}
		else if (camera_position.y < normalYCameraJump && fall == true)
		{
			camera_position.y += (float)getDeltaTime() * 3;
		}
		else if(camera_position.y > normalYCameraPosition)
		{
			camera_position.y -= 0.5 * getDeltaTime() * 8;

			fall = false;
		}

		view_matrix = glm::lookAt(camera_position, camera_position + camera_direction, camera_up);
	}
}