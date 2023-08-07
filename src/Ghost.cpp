#include "Ghost.h"


Ghost::Ghost(double radius_, int steps_, float x, float y, float map_size)
{
    this->radius = radius_;
    this->steps = steps_;
    this->speed = 0.01f;
    this->vertices.resize(1 + ((steps + 1) * (((steps / 2) - 1) / 2 + 1) + steps + 1));
    this->indices.resize((steps + 1) * 3 + ((((steps / 2) - 1) / 2) * (steps + 1) * 6) + steps * 3 + 3);
    this->prev_mov = {0,0};
    this->position = glm::vec3(x, y, 0.f);
    this->rotation = glm::vec3(0.f);
    rotation.x = -90.f;
    this->scale = glm::vec3(1.f);
    this->maze_pos_x = round(position.x / (map_size * 2));
    this->maze_pos_y = round(position.y / (map_size * 2));


    const float angle = 3.1415926 * 2.f / steps;
    vertices[0].pos.x = radius * sin(0); 
    vertices[0].pos.y = -radius * cos(0); 
    vertices[0].pos.z = 0.0f;

    for (int i = 0; i < ((steps / 2) - 1) / 2; i++)
    {
        vertices[1 + (steps + 1) * i].pos.x = radius * sin(angle * (i + 1)); 
        vertices[1 + (steps + 1) * i].pos.y = -radius * cos(angle * (i + 1)); 
        vertices[1 + (steps + 1) * i].pos.z = 0.0f;

        for (int j = 1; j <= steps; j++)
        {
            glm::mat4 trans = glm::mat4(1.0f);
            trans = glm::rotate(trans, angle, glm::vec3(0.0, 1.0, 0.0));
            glm::vec4 newm = trans * glm::vec4(vertices[1 + ((steps + 1) * i + (j - 1))].pos.x,
                                                vertices[1 + ((steps + 1) * i + (j - 1))].pos.y,
                                                vertices[1 + ((steps + 1) * i + (j - 1))].pos.z, 0.0f);
            vertices[1 + ((steps + 1) * i + j)].pos.x = newm[0];
            vertices[1 + ((steps + 1) * i + j)].pos.y = newm[1];
            vertices[1 + ((steps + 1) * i + j)].pos.z = newm[2]; 
        }
    }
    vertices[1 + ((steps + 1) * ((steps / 2) - 1) / 2)].pos.x = vertices[1 + ((steps + 1) * (((steps / 2) - 1) / 2 - 1))].pos.x;
    vertices[1 + ((steps + 1) * ((steps / 2) - 1) / 2)].pos.y = vertices[1 + ((steps + 1) * (((steps / 2) - 1) / 2 - 1))].pos.y + radius;
    vertices[1 + ((steps + 1) * ((steps / 2) - 1) / 2)].pos.z = vertices[1 + ((steps + 1) * (((steps / 2) - 1) / 2 - 1))].pos.z;

    vertices[1 + ((steps + 1) * (((steps / 2) - 1) / 2 + 1))].pos.x = vertices[1 + ((steps + 1) * (((steps / 2) - 1) / 2))].pos.x;  
    vertices[1 + ((steps + 1) * (((steps / 2) - 1) / 2 + 1))].pos.y = vertices[1 + ((steps + 1) * (((steps / 2) - 1) / 2))].pos.y + radius / 2;  
    vertices[1 + ((steps + 1) * (((steps / 2) - 1) / 2 + 1))].pos.z = vertices[1 + ((steps + 1) * (((steps / 2) - 1) / 2))].pos.z;  


    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, angle / 2, glm::vec3(0.0, 1.0, 0.0));
    glm::vec4 newm = trans * glm::vec4(vertices[1 + ((steps + 1) * (((steps / 2) - 1) / 2 + 1))].pos.x,
                                        vertices[1 + ((steps + 1) * (((steps / 2) - 1) / 2 + 1))].pos.y,
                                        vertices[1 + ((steps + 1) * (((steps / 2) - 1) / 2 + 1))].pos.z, 0.0f);

    vertices[1 + ((steps + 1) * (((steps / 2) - 1) / 2 + 1))].pos.x = newm[0];
    vertices[1 + ((steps + 1) * (((steps / 2) - 1) / 2 + 1))].pos.y = newm[1];
    vertices[1 + ((steps + 1) * (((steps / 2) - 1) / 2 + 1))].pos.z = newm[2]; 

    for (int j = 1; j <= steps; j++)
    {
        vertices[1 + ((steps + 1) * ((steps / 2) - 1) / 2 + j)].pos.x = vertices[1 + ((steps + 1) * (((steps / 2) - 1) / 2 - 1) + j)].pos.x;
        vertices[1 + ((steps + 1) * ((steps / 2) - 1) / 2 + j)].pos.y = vertices[1 + ((steps + 1) * (((steps / 2) - 1) / 2 - 1) + j)].pos.y + radius;
        vertices[1 + ((steps + 1) * ((steps / 2) - 1) / 2 + j)].pos.z = vertices[1 + ((steps + 1) * (((steps / 2) - 1) / 2 - 1) + j)].pos.z;

        trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, angle, glm::vec3(0.0, 1.0, 0.0));
        newm = trans * glm::vec4(vertices[1 + ((steps + 1) * (((steps / 2) - 1) / 2 + 1) + (j - 1))].pos.x,
                                vertices[1 + ((steps + 1) * (((steps / 2) - 1) / 2 + 1) + (j - 1))].pos.y,
                                vertices[1 + ((steps + 1) * (((steps / 2) - 1) / 2 + 1) + (j - 1))].pos.z, 0.0f);
        vertices[1 + ((steps + 1) * (((steps / 2) - 1) / 2 + 1) + j)].pos.x = newm[0];
        vertices[1 + ((steps + 1) * (((steps / 2) - 1) / 2 + 1) + j)].pos.y = newm[1];
        vertices[1 + ((steps + 1) * (((steps / 2) - 1) / 2 + 1) + j)].pos.z = newm[2];
    }

    for (int i = 0; i <= steps; i++)
    {
        indices[i * 3] = 0;
        indices[i * 3 + 1] = i + 1;  
        indices[i * 3 + 2] = i + 2;
    }
    for (int i = 1; i < ((steps / 2) - 1) / 2; i++)
    {

        for (int j = 0; j <= steps; j++)
        {
            indices[(steps + 1) * 3 + ((i - 1) * (steps + 1) * 6) + j * 6] = 1 + (steps + 1) * (i - 1) + j;
            indices[(steps + 1) * 3 + ((i - 1) * (steps + 1) * 6) + j * 6 + 1] = 1 + (steps + 1) * (i - 1) + j + 1;
            indices[(steps + 1) * 3 + ((i - 1) * (steps + 1) * 6) + j * 6 + 2] = 1 + (steps + 1) * i + j;

            indices[(steps + 1) * 3 + ((i - 1) * (steps + 1) * 6) + j * 6 + 3] = 1 + (steps + 1) * (i - 1) + j + 1;
            indices[(steps + 1) * 3 + ((i - 1) * (steps + 1) * 6) + j * 6 + 4] = 1 + (steps + 1) * i + j;
            indices[(steps + 1) * 3 + ((i - 1) * (steps + 1) * 6) + j * 6 + 5] = 1 + (steps + 1) * i + j + 1;
        }
    }

    for (int j = 0; j <= steps; j++)
    {
        indices[(steps + 1) * 3 + ((((steps / 2) - 1) / 2 - 1) * (steps + 1) * 6) + j * 6] = 1 + (steps + 1) * (((steps / 2) - 1) / 2 - 1) + j;
        indices[(steps + 1) * 3 + ((((steps / 2) - 1) / 2 - 1) * (steps + 1) * 6) + j * 6 + 1] = 1 + (steps + 1) * (((steps / 2) - 1) / 2 - 1) + j + 1;
        indices[(steps + 1) * 3 + ((((steps / 2) - 1) / 2 - 1) * (steps + 1) * 6) + j * 6 + 2] = 1 + (steps + 1) * ((steps / 2) - 1) / 2 + j;

        indices[(steps + 1) * 3 + ((((steps / 2) - 1) / 2 - 1) * (steps + 1) * 6) + j * 6 + 3] = 1 + (steps + 1) * (((steps / 2) - 1) / 2 - 1) + j + 1;
        indices[(steps + 1) * 3 + ((((steps / 2) - 1) / 2 - 1) * (steps + 1) * 6) + j * 6 + 4] = 1 + (steps + 1) * ((steps / 2) - 1) / 2 + j;
        indices[(steps + 1) * 3 + ((((steps / 2) - 1) / 2 - 1) * (steps + 1) * 6) + j * 6 + 5] = 1 + (steps + 1) * ((steps / 2) - 1) / 2 + j + 1;
    }

    for (int j = 0; j <= steps; j++)
    {
        indices[(steps + 1) * 3 + ((((steps / 2) - 1) / 2) * (steps + 1) * 6) + j * 3] = 1 + (steps + 1) * (((steps / 2) - 1) / 2) + j;
        indices[(steps + 1) * 3 + ((((steps / 2) - 1) / 2) * (steps + 1) * 6) + j * 3 + 1] = 1 + (steps + 1) * (((steps / 2) - 1) / 2) + j + 1;
        indices[(steps + 1) * 3 + ((((steps / 2) - 1) / 2) * (steps + 1) * 6) + j * 3 + 2] = 1 + (steps + 1) * (((steps / 2) - 1) / 2 + 1) + j;
    }


    vao.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    VBO vbo(vertices);
    // Generates Element Buffer Object and links it to indices
    EBO ebo(indices);
    // Links VBO attributes such as coordinates and colors to VAO
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);

    // Unbind all to prevent accidentally modifying them
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
}

Ghost::~Ghost()
{

}

bool Ghost::check_colission(std::vector<Blocc*> &blocks,glm::vec3 direction, float map_size)
{
    bool touch = true;
    glm::vec3 half_extents = glm::vec3(map_size, map_size, map_size);
    for(int i = 0; i < blocks.size(); i++)
    {
        glm::vec3 difference = (this->position + direction) - blocks[i]->center_point;
        glm::vec3 clamped = glm::clamp(difference, -half_extents, half_extents);
        glm::vec3 closest = blocks[i]->center_point + clamped;
        difference = closest - (this->position + direction);
        if(glm::length(difference) <= (this->radius * this->scale.x))
        {
            touch = false;
        }
    }
    return touch;
}   

void Ghost::move(Maze & map, float map_size)
{
    std::vector<std::vector<int>> posibles = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

    if (prev_mov[0] == 0 && prev_mov[1] == 0)
    {
        prev_mov = posibles[0];
    }
    
    glm::vec3 direction(speed * prev_mov[0], speed * prev_mov[1], 0.0f);

    if (check_colission(map.blocks, direction, map_size))
    {
        position += direction;
    }
    else
    {
        int index = std::rand() % posibles.size();
        prev_mov = posibles[index];
    }
}

void Ghost::draw(Shader &shaderProgram)
{
     shaderProgram.use();

    // create transformations
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);

    shaderProgram.setMat4("model", model);

    vao.Bind();

    shaderProgram.setFloat4("ourColor",  0.0f, 1.0f, 0.0f, 1.0f);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)(0));
}