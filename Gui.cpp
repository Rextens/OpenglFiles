#include "Gui.h"

GLuint GuiSlots::guiShaders = 0;
GLint GuiSlots::colourUniform = 0;

GuiSlots::GuiSlots(Rendering &render)
{
	guiShaders = render.loadShader(Logining::gameFiles + "/Game/Shaders/guiShader.vert", Logining::gameFiles + "/Game/Shaders/guiShader.frag");
	colourUniform = render.findUniform(guiShaders, "colours");
}

Gui::Gui(Vertices &vertices)
{
	glGenVertexArrays(1, &vao); //dzia³a jak glGenBuffers, ale na wierzcho³ki //work like glGenBuffers, but on vertices
	glBindVertexArray(vao); //uaktywanie wierzcho³ki //enable vertices
	glBindBuffer(GL_ARRAY_BUFFER, vertices.vbo);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL); //po kolei: indeks, ile wymiarów, typ danych, normalizacja //index, how many dimensions, data type, normalization
	glBindBuffer(GL_ARRAY_BUFFER, vertices.textureVbo);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0); //uaktywniamy index //we enabled index
	glEnableVertexAttribArray(1);
}

Gui::~Gui()
{
}
void Gui::draw(Vertices &vertices)
{
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertices.vertices.size() / 2);
}
void Gui::setColour(glm::vec3 &colours)
{
	Rendering::setUniform(GuiSlots::colourUniform, colours);
}