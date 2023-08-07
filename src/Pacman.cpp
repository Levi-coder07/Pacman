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
    this->powerup_max_timer = 2500.f;
    this->powerup_timer = 0.0f;
    this->in_powerup = false;
    this->going_powerup = false;
    this->leaving_powerup = false;
    this->position = glm::vec3(0.f);
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
Pacman::~Pacman() 
{
    
}

void Pacman::activate_powerup()
{
    this->in_powerup = true;
    this->going_powerup = true;
}

void Pacman::disable_powerup()
{
    this->in_powerup = false;
    this->leaving_powerup = true;
}

bool Pacman::check_colission(std::vector<Blocc*> &blocks,glm::vec3 direction, float map_size)
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

void Pacman::updateInput(GLFWwindow * window,std::vector<Blocc*> blocks, float map_size, Camera & camera)
{
    glm::vec3 direction(0.0f, 0.0f, 0.0f);
    if (glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS)
    {
        rotation.y += 0.1f;
    }
    if (glfwGetKey(window,GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        rotation.y -= 0.1f;
    }
    if (glfwGetKey(window,GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        rotation.x += 0.1f;
    }
    if (glfwGetKey(window,GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        rotation.x -= 0.1f;
    }
    if (glfwGetKey(window,GLFW_KEY_F) == GLFW_PRESS)
    {
        rotation.z += 0.1f;
    }
    if (glfwGetKey(window,GLFW_KEY_G) == GLFW_PRESS)
    {
        rotation.z -= 0.1f;
    }
    if (glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
    {
        direction = glm::vec3(-speed, 0.0f, 0.0f);
        rotation = glm::vec3(0.f, 0.f, 180.f);
    }
    else if (glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
    {
        direction = glm::vec3(speed, 0.0f, 0.0f);
        rotation = glm::vec3(0.f, 0.f, 0.f);
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
        direction = glm::vec3(0.0f, speed, 0.0f);
        rotation = glm::vec3(0.f, 0.f, 90.f);
    }
    else if (glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS)
    {
        direction = glm::vec3(0.0f, -speed, 0.0f);
        rotation = glm::vec3(0.f, 0.f, -90.f);
    }

    if (direction != glm::vec3(0.0f, 0.0f, 0.0f))
    {
        bool touch = this->check_colission(blocks, direction, map_size);
        if (touch)
        {
            position.x += direction.x;
            position.y += direction.y;
            camera.position.x += direction.x;
            camera.position.y += direction.y;
        }
    }
}
void Pacman::draw(Shader &shaderProgram)
{
    shaderProgram.use();

    if (this->in_powerup)
    {
        if (this->powerup_timer >= this->powerup_max_timer)
        {
            this->powerup_timer = 0.f;
            this->disable_powerup();
        }
        else 
        {
            this->powerup_timer += 0.1f;
        }
    }

    if (this->going_powerup)
    {
        if (this->scale.x < 2.f)
        {
            this->scale.x += 0.001f;
            this->scale.y += 0.001f;
            this->scale.z += 0.001f;
        }
        else
        {
            this->scale = glm::vec3(2.f,2.f,2.f);
            this->going_powerup = false;
        }
    }

    if (this->leaving_powerup)
    {
        if (this->scale.x > 1.f)
        {
            this->scale.x -= 0.001f;
            this->scale.y -= 0.001f;
            this->scale.z -= 0.001f;
        }
        else
        {
            this->scale = glm::vec3(1.f,1.f,1.f);
            this->leaving_powerup = false;
        }
    }

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
    
    
    if (!this->in_powerup) shaderProgram.setFloat4("ourColor",  1.0f, 0.8f, 0.0f, 1.0f);
    else shaderProgram.setFloat4("ourColor",  1.0f, sin(glfwGetTime() * 10) + 1.f, 0.0f, 1.0f);
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