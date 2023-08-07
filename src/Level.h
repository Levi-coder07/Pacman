#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "Pacman.h"
#include "Maze.h"
#include "Food.h"
#include "Camera.h"
#include "Ghost.h"
#include "text_renderer.h"

class Level
{
public:
    Maze * map;
    Pacman * pacman;
    
    std::vector<Food*> food_vector;
    std::vector<Ghost*> ghosts;
    std::vector<bool> ghosts_t;
    std::vector<bool> food_eat;
    TextRenderer* text_renderer;
    bool startGame = false;
    bool game_over = false;
    bool instruccion = false;
    Level(glm::vec3 start_pos, std::vector<std::string> matrix);
    void render_level(GLFWwindow * window, Shader & color_shader, Shader & texture_shader, Shader & text_shader, Camera & camera);
};

#endif