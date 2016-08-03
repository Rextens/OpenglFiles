#include "Rendering.h"

Rendering::Rendering()
{

}
GLint Rendering::loadShader(std::string wayToVertexShader, std::string wayToFragmentShader)
{
	//jaki shader chcemy zrobiæ
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertex_shader_data;
	std::ifstream vertexShaderFile(wayToVertexShader.c_str(), std::ios::in);
	if(vertexShaderFile.is_open())
	{
		std::string line;
		while (std::getline(vertexShaderFile, line))
		{
			vertex_shader_data += "\n" + line;
		}
		vertexShaderFile.close();
	}

	std::string fragment_shader_data;
	std::ifstream fragmentShaderFile(wayToFragmentShader.c_str(), std::ios::in);
	if(fragmentShaderFile.is_open())
	{
		std::string line;
		while (std::getline(fragmentShaderFile, line))
			fragment_shader_data += "\n" + line;

		fragmentShaderFile.close();
	}

	const char *vertex_ptr = vertex_shader_data.c_str();
	const char *fragment_ptr = fragment_shader_data.c_str();

	//wstawia kod shadera do obiektu shadera
	glShaderSource(vertexShaderId, 1, &vertex_ptr, NULL);
	glShaderSource(fragmentShaderId, 1, &fragment_ptr, NULL);

	//kompiluje shadery
	glCompileShader(vertexShaderId);
	glCompileShader(fragmentShaderId);

	//tworzy program sahdera
	GLuint shaderProgram = glCreateProgram();

	//³¹czy shadery
	glAttachShader(shaderProgram, vertexShaderId);
	glAttachShader(shaderProgram, fragmentShaderId);

	//dodaje shadery do programu
	glLinkProgram(shaderProgram);

	//usuwa zajêt¹ pamiêæ
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	int vertexShaderStatus = -1;
	//sprawdza stan kompilacji shaders
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &vertexShaderStatus);
	if(vertexShaderStatus != GL_TRUE)
	{
		std::cout << "Vertex shader " << wayToVertexShader << "compile error" << std::endl;

		return 1;
	}
	int fragmentShaderStatus = -1;
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &fragmentShaderStatus);
	if(vertexShaderStatus != GL_TRUE)
	{
		std::cout << "Vertex shader " << wayToVertexShader << "compile error" << std::endl;

		return 2;
	}

	glLinkProgram(shaderProgram);
	int linkStatus = -1;
	//sprawdza stan linkowania shadera
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);
	if(linkStatus != GL_TRUE)
	{
		std::cout << "Shader programme link error!" << std::endl;

		return 3;
	}
	const int maxLength = 2048;
	int length = 0;
	char logText[maxLength];
	//pokazuje szczegó³owy proces logów shadera
	glGetProgramInfoLog(shaderProgram, maxLength, &length, logText);
	std::cout << logText;

	return shaderProgram;
}

int Rendering::loadTexture(std::string wayToTexture)
{
	FREE_IMAGE_FORMAT imageFormat = FIF_UNKNOWN;
	FIBITMAP *imagePTR = 0;
	BYTE *bits = 0;

	imageFormat = FreeImage_GetFileType(wayToTexture.c_str(), 0);
	if(imageFormat == FIF_UNKNOWN)
	{
		imageFormat = FreeImage_GetFIFFromFilename(wayToTexture.c_str());
	}
	if(FreeImage_FIFSupportsReading(imageFormat))
	{
		imagePTR = FreeImage_Load(imageFormat, wayToTexture.c_str());
	}
	bits = FreeImage_GetBits(imagePTR);
	int imageWidth = 0;
	int imageHeight = 0;

	imageWidth = FreeImage_GetWidth(imagePTR);
	imageHeight = FreeImage_GetHeight(imagePTR);

	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	unsigned int colours = FreeImage_GetBPP(imagePTR);

	if (colours == 24)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, bits);
	}
	else if (colours == 32)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);
	}

	glGenerateMipmap(GL_TEXTURE_2D);
	return 0;
}
int Rendering::loadTexture(std::string wayToFile, GLuint &handle)
{
	FREE_IMAGE_FORMAT image_format = FIF_UNKNOWN;
	FIBITMAP* image_ptr = 0;
	BYTE* bits = 0;

	image_format = FreeImage_GetFileType(wayToFile.c_str(), 0);
	if (image_format == FIF_UNKNOWN)
		image_format = FreeImage_GetFIFFromFilename(wayToFile.c_str());

	if (FreeImage_FIFSupportsReading(image_format))
		image_ptr = FreeImage_Load(image_format, wayToFile.c_str());

	bits = FreeImage_GetBits(image_ptr);

	int image_width = 0;
	int image_height = 0;
	image_width = FreeImage_GetWidth(image_ptr);
	image_height = FreeImage_GetHeight(image_ptr);
	if ((bits == 0) || (image_width == 0) || (image_height == 0))
		return -1;

	glGenTextures(1, &handle);
	glBindTexture(GL_TEXTURE_2D, handle);

	unsigned int colours = FreeImage_GetBPP(image_ptr);
	if (colours == 24)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0,
			GL_BGR, GL_UNSIGNED_BYTE, bits);
	else if (colours == 32)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height,
			0, GL_BGRA, GL_UNSIGNED_BYTE, bits);
	glGenerateMipmap(GL_TEXTURE_2D);

	return 0;
}
int Rendering::loadTexture(std::string wayToFile, Texture &texture)
{
	FREE_IMAGE_FORMAT image_format = FIF_UNKNOWN;
	FIBITMAP* image_ptr = nullptr;
	BYTE* bits = nullptr;

	image_format = FreeImage_GetFileType(wayToFile.c_str(), 0);
	if (image_format == FIF_UNKNOWN)
		image_format = FreeImage_GetFIFFromFilename(wayToFile.c_str());

	if (FreeImage_FIFSupportsReading(image_format))
		image_ptr = FreeImage_Load(image_format, wayToFile.c_str());

	bits = FreeImage_GetBits(image_ptr);

	unsigned int image_width = 0;
	unsigned int image_height = 0;
	image_width = FreeImage_GetWidth(image_ptr);
	image_height = FreeImage_GetHeight(image_ptr);
	if ((bits == 0) || (image_width == 0) || (image_height == 0))
		return -1;

	texture.bits = bits;
	texture.imagePtr = image_ptr;
	texture.width = image_width;
	texture.height = image_height;

	return 0;
}
void Rendering::glfwInitialization()
{
	if(!glfwInit())
	{
		std::cout << "Error with initialization glfw library" << std::endl;
		glfwTerminate();

		return;
	}
}
void Rendering::glewInitialization()
{
	if(glewInit() != GLEW_OK)
	{
		std::cout << "Error with initialization glew library" << std::endl;

		return;
	}
}
void Rendering::deep()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}
//******************************************************************************
void Rendering::ProcessWindowEvents(GLFWwindow *window)
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}
//******************************************************************************
void Rendering::Terminate(GLFWwindow *window)
{
	glfwDestroyWindow(window);
	glfwTerminate();
}
//******************************************************************************
void Rendering::ClearColor(float r, float g, float b, float alpha, int windowWidth, int windowHeight)
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, windowWidth, windowHeight);
}
int Rendering::findUniform(GLuint shader_program, std::string uniform_name)
{
	GLint result = glGetUniformLocation(shader_program, uniform_name.c_str());

	if (result == -1)
		std::cout << "Uniform \"" << uniform_name << "\" not found." << std::endl;

	return result;
}
void Rendering::setUniform(GLint uniform_handle, GLint value)
{
	glUniform1iv(uniform_handle, 1, &value);
}
//******************************************************************************
void Rendering::setUniform(GLint uniform_handle, const glm::mat4 &matrix)
{
	glUniformMatrix4fv(uniform_handle, 1, GL_FALSE, glm::value_ptr(matrix));
}
void Rendering::setUniform(GLint uniform_handle, glm::vec3 &value)
{
	glUniform3f(uniform_handle, value.x, value.y, value.z);
}