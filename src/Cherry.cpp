#include "Cherry.h"

Cherry::Cherry(double radius_, int steps_, float x, float y)
{
    this->radius = radius_;
    this->steps = steps_;

    int vert_pos = (steps + 1) * (steps / 2 - 1) + 2;
    int index_pos = (steps + 1) * 3 + (((steps / 2) - 1 - 1) * (steps + 1) * 6) + steps * 3 + 3;
    float dif = radius;

    this->vertices.resize(vert_pos * 2 + 10);
    this->indices.resize(index_pos * 2 + 24);

    this->position = glm::vec3(0.f);
    position.x = x;
    position.y = y;

    this->rotation = glm::vec3(0.f);
    this->rotation.x = 90.f;
    this->scale = glm::vec3(1.f);
    
    this->is_eaten = false;

    const float angle = 3.1415926 * 2.f / steps;
    vertices[0].pos.x = radius * sin(0); 
    vertices[0].pos.y = -radius * cos(0); 
    vertices[0].pos.z = 0.0f;

    vertices[vert_pos].pos.x = radius * sin(0) + dif; 
    vertices[vert_pos].pos.y = -radius * cos(0); 
    vertices[vert_pos].pos.z = 0.0f;

    for (int i = 0; i < (steps / 2) - 1; i++)
    {
        vertices[1 + (steps + 1) * i].pos.x = radius * sin(angle * (i + 1)); 
        vertices[1 + (steps + 1) * i].pos.y = -radius * cos(angle * (i + 1)); 
        vertices[1 + (steps + 1) * i].pos.z = 0.0f;

        vertices[vert_pos + 1 + (steps + 1) * i].pos.x = radius * sin(angle * (i + 1)) + dif; 
        vertices[vert_pos + 1 + (steps + 1) * i].pos.y = -radius * cos(angle * (i + 1)); 
        vertices[vert_pos + 1 + (steps + 1) * i].pos.z = 0.0f;

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

            vertices[vert_pos + 1 + ((steps + 1) * i + j)].pos.x = newm[0] + dif;
            vertices[vert_pos + 1 + ((steps + 1) * i + j)].pos.y = newm[1];
            vertices[vert_pos + 1 + ((steps + 1) * i + j)].pos.z = newm[2];  
        }
    }
    vertices[1 + ((steps + 1) * (steps / 2 - 1))].pos.x =  radius * sin(angle * (steps / 2)); 
    vertices[1 + ((steps + 1) * (steps / 2 - 1))].pos.y = -radius * cos(angle * (steps / 2)); 
    vertices[1 + ((steps + 1) * (steps / 2 - 1))].pos.z = 0.0f;

    vertices[vert_pos + 1 + ((steps + 1) * (steps / 2 - 1))].pos.x =  radius * sin(angle * (steps / 2)) + dif; 
    vertices[vert_pos + 1 + ((steps + 1) * (steps / 2 - 1))].pos.y = -radius * cos(angle * (steps / 2)); 
    vertices[vert_pos + 1 + ((steps + 1) * (steps / 2 - 1))].pos.z = 0.0f;

    for (int i = 0; i < vert_pos; i++)
    {
        vertices[i].pos.x -= dif;
    }

    for (int i = 0; i <= steps; i++)
    {
        indices[i * 3] = 0;
        indices[i * 3 + 1] = i + 1;  
        indices[i * 3 + 2] = i + 2;

        indices[index_pos + i * 3] = vert_pos;
        indices[index_pos + i * 3 + 1] = vert_pos + i + 1;  
        indices[index_pos + i * 3 + 2] = vert_pos + i + 2;
    }
    for (int i = 1; i < (steps / 2) - 1; i++)
    {

        for (int j = 0; j <= steps; j++)
        {
            indices[(steps + 1) * 3 + ((i - 1) * (steps + 1) * 6) + j * 6] = 1 + (steps + 1) * (i - 1) + j;
            indices[(steps + 1) * 3 + ((i - 1) * (steps + 1) * 6) + j * 6 + 1] = 1 + (steps + 1) * (i - 1) + j + 1;
            indices[(steps + 1) * 3 + ((i - 1) * (steps + 1) * 6) + j * 6 + 2] = 1 + (steps + 1) * i + j;

            indices[(steps + 1) * 3 + ((i - 1) * (steps + 1) * 6) + j * 6 + 3] = 1 + (steps + 1) * (i - 1) + j + 1;
            indices[(steps + 1) * 3 + ((i - 1) * (steps + 1) * 6) + j * 6 + 4] = 1 + (steps + 1) * i + j;
            indices[(steps + 1) * 3 + ((i - 1) * (steps + 1) * 6) + j * 6 + 5] = 1 + (steps + 1) * i + j + 1;

            indices[index_pos + (steps + 1) * 3 + ((i - 1) * (steps + 1) * 6) + j * 6] = vert_pos + 1 + (steps + 1) * (i - 1) + j;
            indices[index_pos + (steps + 1) * 3 + ((i - 1) * (steps + 1) * 6) + j * 6 + 1] = vert_pos + 1 + (steps + 1) * (i - 1) + j + 1;
            indices[index_pos + (steps + 1) * 3 + ((i - 1) * (steps + 1) * 6) + j * 6 + 2] = vert_pos + 1 + (steps + 1) * i + j;

            indices[index_pos + (steps + 1) * 3 + ((i - 1) * (steps + 1) * 6) + j * 6 + 3] = vert_pos + 1 + (steps + 1) * (i - 1) + j + 1;
            indices[index_pos + (steps + 1) * 3 + ((i - 1) * (steps + 1) * 6) + j * 6 + 4] = vert_pos + 1 + (steps + 1) * i + j;
            indices[index_pos + (steps + 1) * 3 + ((i - 1) * (steps + 1) * 6) + j * 6 + 5] = vert_pos + 1 + (steps + 1) * i + j + 1;
        }
    }

    for (int i = 0; i <= steps; i++)
    {
        indices[(steps + 1) * 3 + (((steps / 2) - 1 - 1) * (steps + 1) * 6) + i * 3] = 1 + (steps + 1) * ((steps / 2) - 2) + i;
        indices[(steps + 1) * 3 + (((steps / 2) - 1 - 1) * (steps + 1) * 6) + i * 3 + 1] = 1 + (steps + 1) * ((steps / 2) - 2) + i + 1;
        indices[(steps + 1) * 3 + (((steps / 2) - 1 - 1) * (steps + 1) * 6) + i * 3 + 2] = 1 + (steps + 1) * ((steps / 2) - 1);

        indices[index_pos + (steps + 1) * 3 + (((steps / 2) - 1 - 1) * (steps + 1) * 6) + i * 3] = vert_pos + 1 + (steps + 1) * ((steps / 2) - 2) + i;
        indices[index_pos + (steps + 1) * 3 + (((steps / 2) - 1 - 1) * (steps + 1) * 6) + i * 3 + 1] = vert_pos + 1 + (steps + 1) * ((steps / 2) - 2) + i + 1;
        indices[index_pos + (steps + 1) * 3 + (((steps / 2) - 1 - 1) * (steps + 1) * 6) + i * 3 + 2] = vert_pos + 1 + (steps + 1) * ((steps / 2) - 1);
    }


    vertices[vert_pos * 2].pos = glm::vec3(vertices[0].pos.x + radius / 5, radius, radius / 5);
    vertices[vert_pos * 2 + 1].pos = glm::vec3(vertices[0].pos.x - radius / 5, radius, radius / 5);
    vertices[vert_pos * 2 + 2].pos = glm::vec3(vertices[0].pos.x + radius / 5, radius, -radius / 5);
    vertices[vert_pos * 2 + 3].pos = glm::vec3(vertices[0].pos.x - radius / 5, radius, -radius / 5);
    vertices[vert_pos * 2 + 4].pos = glm::vec3(0, radius * 3, 0);

    vertices[vert_pos * 2 + 5].pos = glm::vec3(vertices[vert_pos].pos.x + radius / 5, radius, radius / 5);
    vertices[vert_pos * 2 + 6].pos = glm::vec3(vertices[vert_pos].pos.x - radius / 5, radius, radius / 5);
    vertices[vert_pos * 2 + 7].pos = glm::vec3(vertices[vert_pos].pos.x + radius / 5, radius, -radius / 5);
    vertices[vert_pos * 2 + 8].pos = glm::vec3(vertices[vert_pos].pos.x - radius / 5, radius, -radius / 5);
    vertices[vert_pos * 2 + 9].pos = glm::vec3(0, radius * 3, 0);

    indices[index_pos * 2] = vert_pos * 2;
    indices[index_pos * 2 + 1] = vert_pos * 2 + 1;
    indices[index_pos * 2 + 2] = vert_pos * 2 + 4;

    indices[index_pos * 2 + 3] = vert_pos * 2 + 2;
    indices[index_pos * 2 + 4] = vert_pos * 2 + 3;
    indices[index_pos * 2 + 5] = vert_pos * 2 + 4;

    indices[index_pos * 2 + 6] = vert_pos * 2;
    indices[index_pos * 2 + 7] = vert_pos * 2 + 2;
    indices[index_pos * 2 + 8] = vert_pos * 2 + 4;

    indices[index_pos * 2 + 9] = vert_pos * 2 + 1;
    indices[index_pos * 2 + 10] = vert_pos * 2 + 3;
    indices[index_pos * 2 + 11] = vert_pos * 2 + 4;

    indices[index_pos * 2 + 12] = vert_pos * 2 + 5;
    indices[index_pos * 2 + 13] = vert_pos * 2 + 6;
    indices[index_pos * 2 + 14] = vert_pos * 2 + 9;

    indices[index_pos * 2 + 15] = vert_pos * 2 + 7;
    indices[index_pos * 2 + 16] = vert_pos * 2 + 8;
    indices[index_pos * 2 + 17] = vert_pos * 2 + 9;

    indices[index_pos * 2 + 18] = vert_pos * 2 + 5;
    indices[index_pos * 2 + 19] = vert_pos * 2 + 7;
    indices[index_pos * 2 + 20] = vert_pos * 2 + 9;

    indices[index_pos * 2 + 21] = vert_pos * 2 + 6;
    indices[index_pos * 2 + 22] = vert_pos * 2 + 8;
    indices[index_pos * 2 + 23] = vert_pos * 2 + 9;


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
Cherry::~Cherry() 
{
    
}

void Cherry::draw(Shader &shaderProgram)
{
    shaderProgram.use();

    shaderProgram.setFloat4("ourColor", 1.0, 0.0, 0.0, 1.0);

    // create transformations
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);


    shaderProgram.setMat4("model", model);


        // create transformations
    
    vao.Bind();
    int index_pos = (steps + 1) * 3 + (((steps / 2) - 1 - 1) * (steps + 1) * 6) + steps * 3 + 3;
    glDrawElements(GL_TRIANGLES, index_pos * 2, GL_UNSIGNED_INT, (void*)(0));


    shaderProgram.setFloat4("ourColor", 0.58, 0.29, 0.0, 1.0);
    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, (void*)((index_pos * 2) * sizeof(float)));

}