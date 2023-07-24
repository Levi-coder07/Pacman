#include "Food.h"

Food::Food(double radius_, int steps_, float x, float y)
{
    this->radius = radius_;
    this->steps = steps_;
    this->vertices.resize((steps + 1) * (steps / 2 - 1) + 3);
    this->indices.resize(((steps + 1) * (steps / 2 - 1) * 6) + ((steps + 1) * (steps / 2 - 1) * 3) + steps * 3 + 3);

    this->position = glm::vec3(0.f);
    position.x = x;
    position.y = y;

    this->rotation = glm::vec3(0.f);
    this->scale = glm::vec3(1.f);
    
    this->is_eaten = false;

    const float angle = 3.1415926 * 2.f / steps;
    vertices[0].pos.x = radius * sin(0); 
    vertices[0].pos.y = -radius * cos(0); 
    vertices[0].pos.z = 0.0f;

    for (int i = 0; i < (steps / 2) - 1; i++)
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
    vertices[1 + ((steps + 1) * (steps / 2 - 1))].pos.x =  radius * sin(angle * (steps / 2)); 
    vertices[1 + ((steps + 1) * (steps / 2 - 1))].pos.y = -radius * cos(angle * (steps / 2)); 
    vertices[1 + ((steps + 1) * (steps / 2 - 1))].pos.z = 0.0f;

    vertices[1 + ((steps + 1) * (steps / 2 - 1)) + 1].pos.x = 0.0f;
    vertices[1 + ((steps + 1) * (steps / 2 - 1)) + 1].pos.y = 0.0f; 
    vertices[1 + ((steps + 1) * (steps / 2 - 1)) + 1].pos.z = 0.0f;

    for (int i = 0; i <= steps; i++)
    {
        indices[i * 3] = 0;
        indices[i * 3 + 1] = i + 1;  
        indices[i * 3 + 2] = i + 2;

        indices[((steps + 1) * (steps / 2 - 1) * 6) + i * 3] = (steps + 1) * (steps / 2 - 1) + 2;
        indices[((steps + 1) * (steps / 2 - 1) * 6) + i * 3 + 1] =  i + 1;
        indices[((steps + 1) * (steps / 2 - 1) * 6) + i * 3 + 2] = 0;

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

            indices[((steps + 1) * (steps / 2 - 1) * 6) + ((steps + 1) * i * 3) + j * 3] = 1 + (steps + 1) * (i - 1) + j;
            indices[((steps + 1) * (steps / 2 - 1) * 6) + ((steps + 1) * i * 3) + j * 3 + 1] = 1 + (steps + 1) * i + j;
            indices[((steps + 1) * (steps / 2 - 1) * 6) + ((steps + 1) * i * 3) + j * 3 + 2] = (steps + 1) * (steps / 2 - 1) + 2;

        }
    }

    for (int i = 0; i <= steps; i++)
    {
        indices[(steps + 1) * 3 + (((steps / 2) - 1 - 1) * (steps + 1) * 6) + i * 3] = 1 + (steps + 1) * ((steps / 2) - 2) + i;
        indices[(steps + 1) * 3 + (((steps / 2) - 1 - 1) * (steps + 1) * 6) + i * 3 + 1] = 1 + (steps + 1) * ((steps / 2) - 2) + i + 1;
        indices[(steps + 1) * 3 + (((steps / 2) - 1 - 1) * (steps + 1) * 6) + i * 3 + 2] = 1 + (steps + 1) * ((steps / 2) - 1);

        indices[((steps + 1) * (steps / 2 - 1) * 6) + ((steps + 1) * (steps / 2 - 1) * 3) + i * 3] = (steps + 1) * (steps / 2 - 1) + 2;
        indices[((steps + 1) * (steps / 2 - 1) * 6) + ((steps + 1) * (steps / 2 - 1) * 3) + i * 3 + 1] = 1 + (steps + 1) * (steps / 2 - 2) + i;
        indices[((steps + 1) * (steps / 2 - 1) * 6) + ((steps + 1) * (steps / 2 - 1) * 3) + i * 3 + 2] = (steps + 1) * (steps / 2 - 1) + 1;
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
int Food::get_vertices_size()
{
    return this->vertices.size();
}
int Food::get_indices_size()
{
    return this->indices.size();
}
Food::~Food() 
{
    
}

void Food::draw(Shader &shaderProgram)
{
    shaderProgram.use();

    shaderProgram.setFloat4("ourColor", 1.0, 1.0, 1.0, 1.0);

    // create transformations
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);

    shaderProgram.setMat4("model", model);


        // create transformations
    
    vao.Bind();

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)(0));
}