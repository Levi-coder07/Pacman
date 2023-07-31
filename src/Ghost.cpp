#include "Ghost.h"


Ghost::Ghost(double radius_, int steps_, float x, float y)
{
    this->touched = false;
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

void Ghost::move(std::vector<std::string> matrix, float map_size)
{
    int x = position.x / (map_size * 2);
    int y = position.y / (map_size * 2);

    std::vector<std::vector<int>> posibles;
    
    if (x > 0 && matrix[x - 1][y] != '#')
    {
        posibles.push_back({-1, 0});
    }
    if (x < matrix.size() - 1 && matrix[x + 1][y] != '#')
    {
        posibles.push_back({1, 0});
    }
    if (y > 0 && matrix[x][y - 1] != '#')
    {
        posibles.push_back({0, -1});
    }
    if (y < matrix[x].size() - 1 && matrix[x][y + 1] != '#')
    {
        posibles.push_back({0, 1});
    }

    if (posibles.size() == 2 && (posibles[0][0] * - 1) == posibles[1][0] && (posibles[0][1] * - 1) == posibles[1][1])
    {
        if (prev_mov[0] == 0 && prev_mov[1] == 0)
        {
            prev_mov = posibles[0];
        }
        position.x += (float)prev_mov[0] * speed;
        position.y += (float)prev_mov[1] * speed;
    }
    else
    {
        int index = std::rand() % posibles.size();

        position.x += (float)posibles[index][0] * speed;
        position.y += (float)posibles[index][1] * speed;

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