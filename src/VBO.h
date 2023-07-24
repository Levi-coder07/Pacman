#ifndef VBO_CLASS_H
#define VBO_CLASS_H
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
struct Vertex
{
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec2 tex_coord;
};

class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(std::vector<Vertex>& vertices);

	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();
};

#endif