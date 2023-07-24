#include"Camera.h"



Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	this->position = position;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position
	view = glm::lookAt(this->position, this->position + this->orientation, this->up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	// Sets new camera matrix
	cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	// Exports camera matrix
	shader.use();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::process_input(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        this->position.x -= this->speed;
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        this->position.x += this->speed;
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        this->position.y += this->speed;
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        this->position.y -= this->speed;
    
}