#include "Vertices.h"



Vertices::Vertices(std::string wayToFile, std::string wayToFileTex)
{
	std::ifstream inputMesh(wayToFile);
	
	if (!inputMesh)
	{
		std::cout << "can't open file with mesh: " << wayToFile.c_str() << std::endl;

		getchar();

		return;
	}
	while (inputMesh.good())
	{
		GLfloat temp;
		inputMesh >> temp;
		vertices.push_back(temp);
	}

	inputMesh.close();

	inputMesh.open(wayToFileTex);

	while (inputMesh.good())
	{
		GLfloat temp;
		inputMesh >> temp;
		texVertices.push_back(temp);
	}

	inputMesh.close();

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &textureVbo);
	glBindBuffer(GL_ARRAY_BUFFER, textureVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * texVertices.size(), texVertices.data(), GL_STATIC_DRAW);
}


Vertices::~Vertices()
{
}