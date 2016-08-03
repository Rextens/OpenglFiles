#pragma once

#include <GL\glew.h>
#include "Vertices.h"
#include "Rendering.h"
#include "Logining.h"

struct GuiSlots
{
	GuiSlots(Rendering &render);
	static GLuint guiShaders;
	static GLint colourUniform;
};

class Gui
{
public:
	Gui(Vertices &vertices);
	~Gui();
	void draw(Vertices &vertices);
	void setColour(glm::vec3 &colours);

	GLuint vao;
};

