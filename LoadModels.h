#pragma once

#include <GL\glew.h>
#include "Rendering.h"

#include <vector>
#include <iostream>

#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <assimp\cimport.h>
struct Vectors
{
	std::vector<GLfloat> mesh_vertices_count;
	std::vector<GLfloat> mesh_starting_vertex_index;
	std::vector<GLuint> textures;
};
class LoadModels
{
public:
	Rendering render;

	GLuint vao = 0;

	LoadModels(std::string file_name, Vectors &vectors);
	~LoadModels();
	void drawModel(GLint textureSlot, Vectors &vectors);
};
