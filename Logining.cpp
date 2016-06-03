#include "Logining.h"



Logining::Logining()
{
}

Logining::~Logining()
{
}
void Logining::loadLogins(std::string logins)
{
	std::fstream file(logins);

	std::string password;
	std::string login;

	std::cin >> login;
	std::cin >> password;

	if (!file)
	{
		std::cout << "Cannnot open file with player name" << std::endl;

		getchar();

		return;
	}

	std::string line;

	loginNow = login;

	std::vector<std::string> board;

	while (std::getline(file, line))
	{
		board.push_back(line);
	}
	for (unsigned int i = 0; i < board.size(); i += 2)
	{
		if (board[i] == Auxiliary::encrypt(login) && board[i + 1] == Auxiliary::encrypt(password))
		{
			logining = !logining;
		
			break;
		}
	}
}
void Logining::registry(std::string wayToFile)
{
	std::ifstream file(wayToFile);
	std::string line;

	if (!file)
	{
		std::cout << "Cannnot open file with registry" << std::endl;
		
		getchar();

		return;
	}

	std::vector<std::string> board;

	while (std::getline(file, line))
	{
		board.push_back(line);
	}

	std::string getLogin;
	std::string password;

	std::cin >> getLogin;
	std::cin >> password;

	for (int i = 0; i < board.size(); i += 2)
	{
		if (board[i] == Auxiliary::encrypt(getLogin))
		{
			std::cout << "This login is existing. Please give me same else" << std::endl;

			getchar();

			return;
		}
	}

	board.push_back(Auxiliary::encrypt(getLogin));
	board.push_back(Auxiliary::encrypt(password));

	file.close();

	std::ofstream output(wayToFile);

	if (!output)
	{
		std::cout << "Cannnot open file" << std::endl;

		getchar();

		exit(0);
	}
	for (unsigned int i = 0; i < board.size(); i++)
	{
		output << board[i] << std::endl;
	}
	
	std::error_code error;
	Auxiliary::createFile("C:/Game/Saves/" + getLogin, error);
	Auxiliary::createFile("C:/Game/Saves/" + getLogin + "/Save", error);
	Auxiliary::createFile("C:/Game/Saves/" + getLogin + "/Save/camera", error);
	Auxiliary::createFile("C:/Game/Saves/" + getLogin + "/Save/Objects", error);
	Auxiliary::createFile("C:/Game/Saves/" + getLogin + "/Save/Player", error);
	Auxiliary::createFile("C:/Game/Saves/" + getLogin + "/Save/Timers", error);
	Auxiliary::createFile("C:/Game/Saves/" + getLogin + "/Save/Statistics", error);

	output.close();

	std::ofstream outputWorld;

	outputWorld.open("C:/Game/Saves/" + getLogin + "/Save/Objects/generateOrbs.txt");
	outputWorld << 0;
	outputWorld.close();
	outputWorld.open("C:/Game/Saves/" + getLogin + "/Save/Objects/generateWorld.txt");
	outputWorld << 0;
	outputWorld.close();
	outputWorld.open("C:/Game/Saves/" + getLogin + "/Save/Objects/howManyOrbs.txt");
	outputWorld.close();
	outputWorld.open("C:/Game/Saves/" + getLogin + "/Save/Objects/saveObjects.txt");
	for (int i = 0; i < 21; i++)
	{
		output << "0 0 0" << std::endl;
	}
	outputWorld.close();
	outputWorld.open("C:/Game/Saves/" + getLogin + "/Save/Objects/saveOrbs.txt");
	outputWorld.close();

	outputWorld.open("C:/Game/Saves/" + getLogin + "/Save/camera/cameraPosition.txt");
	outputWorld << 0 << std::endl;
	outputWorld << 0 << std::endl;
	outputWorld << 0 << std::endl;
	outputWorld.close();

	outputWorld.open("C:/Game/Saves/" + getLogin + "/Save/Player/championClass.txt");
	outputWorld << 1 << std::endl;
	outputWorld.close();
	outputWorld.open("C:/Game/Saves/" + getLogin + "/Save/Player/statistics.txt");
	outputWorld << 0 << std::endl;
	outputWorld << 0 << std::endl;
	outputWorld << 0 << std::endl;
	outputWorld << 0 << std::endl;
	outputWorld << 0 << std::endl;
	outputWorld << 0 << std::endl;
	outputWorld << 0 << std::endl;
	outputWorld << 0 << std::endl;
	outputWorld << 0 << std::endl;
	outputWorld << 0 << std::endl;
	outputWorld << 0 << std::endl;
	outputWorld << 0 << std::endl;
	outputWorld.close();
	outputWorld.open("C:/Game/Saves/" + getLogin + "/Save/Timers/saveTimers.txt");
	outputWorld.close();
	outputWorld.open("C:/Game/Saves/" + getLogin + "/Save/Statistics/statistics.txt");
	outputWorld << 50;
	outputWorld.close();
}

