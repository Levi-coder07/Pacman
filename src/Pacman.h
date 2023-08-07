#ifndef PACMAN_CLASS_H
#define PACMAN_CLASS_H

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
#include "Blocc.h"
#include "Camera.h"
#include "VAO.h"
#include "EBO.h"


class Pacman
{
private:
    int steps;

    float speed;

    float powerup_max_timer;
    float powerup_timer;
    
    bool going_powerup;
    bool leaving_powerup;


public:
    double radius;
    bool in_powerup;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    int pointCounter;

    float speedX;
    float speedY;

	VAO vao;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Pacman(double radius_, int steps_);
    ~Pacman();

    void activate_powerup();
    void disable_powerup();

    bool check_colission(std::vector<Blocc*> &blocks,glm::vec3 direction, float map_size);

	void updateInput(GLFWwindow * window, std::vector<Blocc*> blocks, float map_size, Camera & camera);
    void draw(Shader &shaderProgram);
};

#endif