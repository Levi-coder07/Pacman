#ifndef _BLOCC_H_
#define _BLOCC_H_

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <vector>
#include <random>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "VAO.h"
#include "EBO.h"
#include <stb_image.h>

class Blocc
{
protected:
    double size;
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

	VAO vao;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
    
    Blocc(double size_, float angle, float x, float y);
    void draw(Shader &shaderProgram);
};

#endif