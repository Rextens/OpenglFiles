#include "Figures.h"

Rendering Slots::render;
GLuint Slots::shaders = 0;
GLint Slots::light = 0;
GLint Slots::textureSlot = 0;
GLint Slots::viewUniform = 0;
GLint Slots::perspectiveUniform = 0;
GLint Slots::transforms = 0;

Slots::Slots(Rendering &render)
{
	shaders = render.loadShader(Logining::gameFiles + "/Game/Shaders/vertexShader.vert", Logining::gameFiles + "/Game/Shaders/fragmentShader.frag");
	light = glGetUniformLocation(shaders, "ambientColor");
	textureSlot = glGetUniformLocation(shaders, "basic_texture");
	viewUniform = glGetUniformLocation(shaders, "view_matrix");
	perspectiveUniform = glGetUniformLocation(shaders, "perspective_matrix");
	transforms = glGetUniformLocation(shaders, "transform");
}

Figures::Figures(Vertices &vertices)
{
	glGenVertexArrays(1, &vao); //dzia³a jak glGenBuffers, ale na wierzcho³ki //work like glGenBuffers, but on vertices
	glBindVertexArray(vao); //uaktywanie wierzcho³ki //enable vertices
	glBindBuffer(GL_ARRAY_BUFFER, vertices.vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); //po kolei: indeks, ile wymiarów, typ danych, normalizacja //index, how many dimensions, data type, normalization
	glBindBuffer(GL_ARRAY_BUFFER, vertices.textureVbo);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0); //uaktywniamy index //we enabled index
	glEnableVertexAttribArray(1);

	transform = glm::translate(glm::mat4(1.0f), position + privotPosition);
}
Figures::Figures(Vertices &vertices, Save &save)
{
	static unsigned int id = 0;

	nr = id;
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vertices.vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, vertices.textureVbo);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	transform = glm::translate(glm::mat4(1.0f), position + privotPosition);

	position = save.position[nr];
	
	id++;
}
Figures::Figures()
{

}
Figures::~Figures()
{

}
void Figures::setPosition(glm::vec3 &newPosition)
{
	position = newPosition;
	transform = glm::translate(glm::mat4(1.0f), newPosition);
}
void Figures::setRotate(float angle, glm::vec3 &isActive)
{
	transform = glm::rotate(transform, angle, isActive);
}
void Figures::setScale(glm::vec3 &scaling)
{
	transform = glm::scale(transform, scaling);
}
void Figures::draw(int textureValue, Vertices &vertices)
{
	glUniformMatrix4fv(Slots::transforms, 1, GL_FALSE, glm::value_ptr(transform));
	glUniform1i(Slots::textureSlot, textureValue);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertices.vertices.size() / 3);
}
void Figures::draw(int textureValue, Save &save, Vertices &vertices)
{
	save.position[nr] = position;

	glUniformMatrix4fv(Slots::transforms, 1, GL_FALSE, glm::value_ptr(transform));
	glUniform1i(Slots::textureSlot, textureValue);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertices.vertices.size() / 3);
}
void Figures::take(GLFWwindow *window, GLint &transforms, glm::vec3 yourPosition)
{
	if (glfwGetKey(window, GLFW_KEY_R))
	{
		repeatable.newPosition = yourPosition;
	}
	setPosition(glm::vec3(repeatable.newPosition.x, repeatable.newPosition.y - 0.25, repeatable.newPosition.z));
}
void Figures::moving(glm::vec3 moveValue)
{
	position += moveValue;
	setPosition(position);
}
void Figures::movingTo(glm::vec3 &moveTo, float speed)
{
	repeatable.x = static_cast<float>(moveTo.x) - position.x + privotPosition.x;
	repeatable.z = static_cast<float>(moveTo.z) - position.z + privotPosition.z;
	repeatable.difference = sqrtf(repeatable.x * repeatable.x + repeatable.z * repeatable.z);
	repeatable.velocity.x = (repeatable.x * speed) / repeatable.difference;
	repeatable.velocity.z = (repeatable.z * speed) / repeatable.difference;

	moving(glm::vec3(repeatable.velocity.x * Window::getDeltaTime(), 0.0f, repeatable.velocity.z * Window::getDeltaTime()));
}
void Figures::setPrivot(glm::vec3 privotPosition)
{
	this->privotPosition = privotPosition;
}

Save::Save(std::string savePosition)
{
	std::ifstream file(savePosition);

	if (!file)
	{
		std::cout << "Cannnot open file with positions" << std::endl;
		
		getchar();
		
		exit(0);
	}


	std::string line;
	std::map<int, std::map<int, std::string> > board;

	int y = 0;
	int x = 0;

	while (getline(file, line))
	{	
		for (unsigned int i = 0; i < line.length(); ++i)	
		{
			if (line[i] == ' ')
			{
				x++;
				continue;
			}
			
			board[y][x] += line[i];
		}
		x = 0;
		y++;
	}

	std::map<int, std::map<int, float> >positions;

	for (unsigned int i = 0; i < board.size(); ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			std::stringstream iss;
			std::string inscription = board[i][j];
			float number;
			iss << inscription;
			iss >> number;

			positions[i][j] = number;
		}
	}
	for (unsigned int i = 0; i < board.size(); ++i)
	{
		position[i] = glm::vec3(positions[i][0], positions[i][1], positions[i][2]);
	}
}
void Save::savePos(std::string wayToFile)
{
	std::ofstream output(wayToFile);

	for (unsigned int i = 0; i < position.size(); ++i)
	{
		output << position[i].x << " ";
		output << position[i].y << " ";
		output << position[i].z << std::endl;
	}
}
void Save::checkOrbs(std::string wayToFile)
{
	std::ifstream file(wayToFile);
	
	if (!file)
	{
		std::cout << "Cannnot open file with orbs" << std::endl;
		
		getchar();
		
		exit(0);
	}

	std::string line;

	int y = 0;
	int x = 0;

	while (getline(file, line))
	{
		for (unsigned int i = 0; i < line.length(); ++i)
		{
			if (line[i] == ' ')
			{
				x++;
				continue;
			}

			orbsBoard[y][x] += line[i];
		}
		x = 0;
		y++;
	}
}
void Save::saveOrbs(std::string wayToFile)
{
	std::ofstream output(wayToFile);

	for (unsigned int i = 0; i < orbsBoard.size(); ++i)
	{
		output << orbsBoard[i][0] << " ";
		output << orbsBoard[i][1] << " ";
		output << orbsBoard[i][2] << std::endl;
	}
}
void Save::checkhowManyOrbs(std::string wayToFile)
{
	std::ifstream file(wayToFile);

	if (!file)
	{
		std::cout << "Cannnot open file with orbs" << std::endl;

		getchar();

		exit(0);
	}

	std::string line;

	int y = 0;
	int x = 0;

	std::map<int, std::string> howManyOrbs;

	while (getline(file, line))
	{
		for (unsigned int i = 0; i < line.length(); ++i)
		{
			if (line[i] == ' ')
			{
				x++;
				continue;
			}

			howManyOrbs[y] += line[i];
		}
		x = 0;
		y++;
	}

	for (unsigned int i = 0; i < howManyOrbs.size(); ++i)
	{
		std::stringstream iss;
		std::string inscription = howManyOrbs[i];
		int number;
		iss << inscription;
		iss >> number;

		howMany[i] = number;
	}
}
void Save::saveHowManyOrbs(std::string wayToFile)
{
	std::ofstream output(wayToFile);

	for (unsigned int i = 0; i < howMany.size(); ++i)
	{
		output << howMany[i] << std::endl;
	}
}
void Save::checkTimers(std::string wayToFile)
{
	std::ifstream file(wayToFile);

	if (!file)
	{
		std::cout << "Cannnot open file with orbs" << std::endl;

		getchar();

		exit(0);
	}

	std::string line;

	int y = 0;
	int x = 0;

	std::map<int, std::string> checkTimer;
	
	while (getline(file, line))
	{
		for (unsigned int i = 0; i < line.length(); ++i)
		{
			if (line[i] == ' ')
			{
				x++;
				continue;
			}

			checkTimer[y] += line[i];
		}
		x = 0;
		y++;
	}

	for (unsigned int i = 0; i < checkTimer.size(); ++i)
	{
		std::stringstream iss;
		std::string inscription = checkTimer[i];
		float number;
		iss << inscription;
		iss >> number;

		timers[i] = number;
	}
}
void Save::saveTimers(std::string wayToFile)
{
	std::ofstream output(wayToFile);

	for (unsigned int i = 0; i < timers.size(); ++i)
	{
		output << timers[i] << std::endl;
	}
}
void Save::checkStatistics(std::string wayToFile)
{
	std::ifstream file(wayToFile);

	if (!file)
	{
		std::cout << "Cannnot open file with orbs" << std::endl;

		getchar();

		exit(0);
	}

	std::string line;

	int y = 0;
	int x = 0;

	std::map<int, std::map<int, std::string> > checkStatistics;

	while (getline(file, line))
	{
		for (unsigned int i = 0; i < line.length(); ++i)
		{
			if (line[i] == ' ')
			{
				x++;
				continue;
			}

			checkStatistics[y][x] += line[i];
		}
		x = 0;
		y++;
	}

	for (unsigned int i = 0; i < checkStatistics.size(); ++i)
	{
		for (unsigned int j = 0; j < checkStatistics[i].size(); ++j)
		{
			std::stringstream iss;
			std::string inscription = checkStatistics[i][j];
			float number;
			iss << inscription;
			iss >> number;

			statistics[i][j] = number;
		}
	}
}
void Save::saveStatistics(std::string wayToFile)
{
	std::ofstream output(wayToFile);

	for (unsigned int i = 0; i < statistics.size(); ++i)
	{
		for (unsigned int j = 0; j < statistics[i].size(); ++j)
		{
			output << statistics[i][j] << " ";
		}
		output << std::endl;
	}
}