#include "Maze.h"

Maze::Maze(std::vector<std::string> matrix_, double map_size, std::vector<Texture>& texture)
{
    this->map_size = map_size;
    this->matrix = matrix_;
    this->texture = texture;

    for (int i = 0; i < this->matrix.size(); i++)
    {
        for (int j = 0; j < this->matrix[i].size(); j++)
        {
            if (this->matrix[i][j] == '#')
            {
                this->blocks.push_back(std::move(new Blocc(map_size, 0.f, i * map_size * 2, j * map_size * 2)));
               
            }
        }
    }
    for (int i = 0; i < this->blocks.size(); i++)
    {
        std::cout<<this->blocks[i]->centerPoint.x<<" ";
                std::cout<<this->blocks[i]->centerPoint.y<<" ";
                std::cout<<this->blocks[i]->centerPoint.z<<std::endl;
    }
    
}

void Maze::draw(Shader &shader)
{
    shader.use();
    texture[0].texUnit(shader, "ourTexture", 0);
    texture[0].Bind();
    for (int i = 0; i < this->blocks.size(); i++)
    {
        this->blocks[i]->draw(shader);
    }
} 