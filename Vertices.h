#pragma once

#include <GL\glew.h>
#include <vector>
#include <fstream>
#include <iostream>

class Vertices
{
public:
	GLuint vbo = 0;
	GLuint textureVbo = 0;

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> texVertices;

	Vertices(std::string wayToFile, std::string wayToFileMesh);
	~Vertices();
};

