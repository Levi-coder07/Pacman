#include "StraightBlock.h"

StraightBlock::StraightBlock(double size_, float angle, float x, float y)
{
    this->size = size_;
    this->vertices.resize(8);
    this->indices.resize(36);

    this->position = glm::vec3(0.f);
    this->rotation = glm::vec3(0.f);
    this->scale = glm::vec3(1.f);

    this->rotation.z = angle;
    this->position.x = x;
    this->position.y = y;


    this->vertices[0].pos = glm::vec3(size / 4, size, size);
    this->vertices[1].pos = glm::vec3(- size / 4, size, size); 
    this->vertices[2].pos = glm::vec3(size / 4, -size, size); 
    this->vertices[3].pos = glm::vec3(- size / 4, -size, size); 
    this->vertices[4].pos = glm::vec3(size / 4, size, -size); 
    this->vertices[5].pos = glm::vec3(- size / 4, size, -size); 
    this->vertices[6].pos = glm::vec3(size / 4, -size, -size); 
    this->vertices[7].pos = glm::vec3(-size / 4, -size, -size);

    for (int i = 0; i < 8; i++)
    {
        this->vertices[i].color = glm::vec3(0.0f, 0.0f, 0.0f);

        if (i % 3 == 0)
            this->vertices[i].tex_coord = glm::vec2(0.0f, 1.0f);
        else if (i % 3 == 1)
            this->vertices[i].tex_coord = glm::vec2(1.0f, 1.0f);
        else
            this->vertices[i].tex_coord = glm::vec2(1.0f, 0.0f);
    }

    this->indices =
    {
        0, 1, 2,
        1, 2, 3,
        0, 1, 5,
        0, 4, 5,
        2, 3, 6,
        3, 6, 7,
        1, 3, 5,
        3, 5, 7,
        0, 2, 4,
        2, 4, 6,
        4, 5, 6,
        5, 6, 7
    };

    vao.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    VBO vbo(vertices);
    // Generates Element Buffer Object and links it to indices
    EBO ebo(indices);
    // Links VBO attributes such as coordinates and colors to VAO
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));

    // Unbind all to prevent accidentally modifying them
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
}


void StraightBlock::draw(Shader &shaderProgram)
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

    shaderProgram.setFloat4("ourColor", 0.45f, 0.0f, 0.45f, 1.0f);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)(0));
}