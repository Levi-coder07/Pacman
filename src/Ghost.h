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
#include "Maze.h"
#include "VAO.h"
#include "EBO.h"

class Ghost
{
private:
    int steps;
    float speed;

    std::vector<int> prev_mov;
    int maze_pos_x;
    int maze_pos_y;
public:
    double radius;
    bool touched = false;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

	VAO vao;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Ghost(double radius_, int steps_, float x, float y, float map_size);
    bool check_colission(std::vector<Blocc*> &blocks,glm::vec3 direction, float map_size);

    ~Ghost();
	void move(Maze & map, float map_size);
    void draw(Shader &shaderProgram);

};

#endif