#include "Pacman.h"

Pacman::Pacman(double radius_, int steps_)
{
    this->pointCounter = 0;
    this->radius = radius_;
    this->steps = steps_;
    this->speed = 0.01;
    this->speedX = 0.01;
    this->speedY = 0.01;
    this->vertices.resize((steps + 1) * (steps / 2 - 1) + 3);
    this->indices.resize(((steps + 1) * (steps / 2 - 1) * 6) + ((steps + 1) * (steps / 2 - 1) * 3) + steps * 3 + 3);

    this->position = glm::vec3(0.4f,0.4f,0.f);
    this->rotation = glm::vec3(0.f);
    this->scale = glm::vec3(1.f);

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
int Pacman::get_vertices_size()
{
    return this->vertices.size();
}
int Pacman::get_indices_size()
{
    return this->indices.size();
}
Pacman::~Pacman() 
{
    
}
bool Pacman::CheckColission(std::vector<Blocc*> &blocks,glm::vec3 direction){
    bool touch = true;
    glm::vec3 HalfExtents = glm::vec3(0.2f,0.2f,0.2f);
    for(int i =0;i<blocks.size();i++){
        glm::vec3 difference = (this->position + direction) - blocks[i]->centerPoint;
        glm::vec3 clamped = glm::clamp(difference,-HalfExtents,HalfExtents);
        glm::vec3 closest = blocks[i]->centerPoint + clamped;
        difference = closest - (this->position + direction);
        if(glm::length(difference) <= this->radius)
        {
                touch = false;
        }
        }
    return touch;
}
void Pacman::updateInput(GLFWwindow * window,std::vector<Blocc*> blocks)
{

    if (glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
    {
        glm::vec3 direction(-speedX,0,0);
        bool touch = this->CheckColission(blocks,direction);
        
        if(touch){
            position.x -= speedX;
            rotation = glm::vec3(0.f, 0.f, 180.f);
        }else{
            position.x -= 0;
            rotation = glm::vec3(0.f, 0.f, 180.f);
        }
        
    }
    else if (glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
    {
        glm::vec3 direction(speedX,0,0);
        bool touch = this->CheckColission(blocks,direction);
        
        if(touch){
            position.x += speedX;
            rotation = glm::vec3(0.f, 0.f, 0.f);
        }else{
            position.x += 0;
            rotation = glm::vec3(0.f, 0.f, 0.f);
        }
        
    }
    else if (glfwGetKey(window,GLFW_KEY_Y) == GLFW_PRESS)
    {
        position.z -= speed;
        rotation = glm::vec3(0.f, 90.f, 0.f);
    }
    else if (glfwGetKey(window,GLFW_KEY_H) == GLFW_PRESS)
    {
        position.z += speed;
        rotation = glm::vec3(0.f, -90.f, 0.f);
    }
    else if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
    {
         glm::vec3 direction(0,speedY,0);
        bool touch = this->CheckColission(blocks,direction);
        
        if(touch){
             position.y += speedY;
         rotation = glm::vec3(0.f, 0.f, 90.f);
        }else{
            position.y += 0;
            rotation = glm::vec3(0.f, 0.f, 90.f);
        }
       
    }
    else if (glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS)
    {
       
         glm::vec3 direction(0,-speedY,0);
        bool touch = this->CheckColission(blocks,direction);
        
        if(touch){
             position.y -= speedY;
         rotation = glm::vec3(0.f, 0.f, -90.f);
        }else{
            position.y -= 0;
            rotation = glm::vec3(0.f, 0.f,-90.f);
        }
    }
}
void Pacman::draw(Shader &shaderProgram)
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

    double  timeValue = glfwGetTime();
    int change =  (steps + 1) * 3 - 3 * (int)(sin(timeValue * 20) * (steps / 12) + (steps / 12) + 1);
    shaderProgram.setFloat4("ourColor",  1.0f, 0.8f, 0.0f, 1.0f);
    glDrawElements(GL_TRIANGLES, change - ((steps + 1) * 3 - change), GL_UNSIGNED_INT, (void*)(((steps + 1) * 3 - change) * sizeof(float)));

    for (int i = 0; i < (steps / 2 - 2); i++)
        glDrawElements(GL_TRIANGLES, (change - ((steps + 1) * 3 - change)) * 2, GL_UNSIGNED_INT, (void*)((((steps + 1) * 6 - change * 2) + (steps + 1) * 3 + (steps + 1) * 6 * i) * sizeof(float)));

    glDrawElements(GL_TRIANGLES, change - ((steps + 1) * 3 - change), GL_UNSIGNED_INT, (void*)((((steps + 1) * 3 - change) + (steps + 1) * 3 + (steps + 1) * 6 * (steps / 2 - 2)) * sizeof(float)));

    shaderProgram.setFloat4("ourColor", 0.0f, 0.0f, 0.0f, 1.0f);
    for (int i = 0; i < steps / 2; i++)
    {
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(((steps + 1) * (steps / 2 - 1) * 6 + i * (steps + 1) * 3 + (steps + 1) * 3 - change) * sizeof(float)));
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(((steps + 1) * (steps / 2 - 1) * 6 + i * (steps + 1) * 3 + change) * sizeof(float)));
    }
}