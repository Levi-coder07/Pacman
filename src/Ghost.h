#ifndef _GHOST_H_
#define _GHOST_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <vector>
#include <random>
#include <time.h>
#include <stdlib.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "VAO.h"
#include "EBO.h"

class Ghost
{
private:
    int steps;
    
    float speed;

    std::vector<int> prev_mov;
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

	VAO vao;
    bool touched;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
    double radius;
	Ghost(double radius_, int steps_, float x, float y);
    ~Ghost();
	void move(std::vector<std::string> matrix, float map_size);
    void draw(Shader &shaderProgram);

};

#endif