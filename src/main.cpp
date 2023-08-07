#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Level.h"
#include "text_renderer.h"

const char * vertex_shader_file = "C:\\Users\\Levi\\Downloads\\Pacman_Final\\src\\shader.vert";
const char * fragment_shader_file = "C:\\Users\\Levi\\Downloads\\Pacman_Final\\src\\shader.frag";

const char * vertex_texshader_file = "C:\\Users\\Levi\\Downloads\\Pacman_Final\\src\\texshader.vert";
const char * fragment_texshader_file = "C:\\Users\\Levi\\Downloads\\Pacman_Final\\src\\texshader.frag";

const char * vertex_text_shader_file = "C:\\Users\\Levi\\Downloads\\Pacman_Final\\src\\text_shader.vert";
const char * fragment_text_shader_file = "C:\\Users\\Levi\\Downloads\\Pacman_Final\\src\\text_shader.frag";

const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 1000;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	std::srand(time(NULL));

	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Trabajo Final", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Windo	w
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glEnable(GL_DEPTH_TEST);

	Shader ourShader(vertex_shader_file, fragment_shader_file);
	Shader texShader(vertex_texshader_file, fragment_texshader_file);

	Shader text_rendShader(vertex_text_shader_file,fragment_text_shader_file);
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
    text_rendShader.use();
    glUniformMatrix4fv(glGetUniformLocation(text_rendShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	
	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, -3.0f, 3.f));
	/*
	std::vector<std::string> matrix =
	{{"b---a| |b---a"},
	 {"|   || ||   |"},
	 {"| | cd cd | |"},
	 {"|           |"},
	 {"| | b-----a |"},
	 {"| | |b---a| |"},
	 {"| | ||ba || |"},
	 {"| | |cd| || |"},
	 {"| | c--d cd |"},
	 {"|           |"},
	 {"|   b---a | |"},
	 {"c-- |b-a| | |"},
	 {"|   |c-d| | |"},
	 {"| | c---d | |"},
	 {"| |       | |"},
	 {"| | b---a | |"},
	 {"| | |b-a| | |"},
	 {"| | |c-d| | |"},
	 {"| | c---d | |"},
	 {"|           |"},
	 {"|   | b-a | |"},
	 {"|-  | | | | |"},
	 {"|  -| | | | |"},
	 {"|-  | c-d | |"},
	 {"|           |"},
	 {"| | b-----a |"},
	 {"| | c-----d |"},
	 {"| |         |"},
	 {"| | b---a | |"},
	 {"| | |ba | | |"},
	 {"|   ||| |   |"},
	 {"| | cdc-d | |"},
	 {"| |       | |"},
	 {"|   ba ba   |"},
	 {"c---d| |c---d"},
	};*/

	std::vector<std::string> matrix =
	{{"####### ######"},
	 {"#....##.##...#"},
	 {"#.##.##.##.#.#"},
	 {"#.##..@..#...#"},
	 {"#.##.#.#...#.#"},
	 {"#.##.#.#.#.#@#"},
	 {"#.##.##.####.#"},
	 {"#.##.#...###.#"},
	 {"#....@.#...#.#"},
	 {"##############"},
	};	

	Level level1(glm::vec3(0.4f, 0.4f, 0.0f), matrix);

	std::string points ;
	TextRenderer text_renderer= TextRenderer(SCR_HEIGHT,SCR_WIDTH);
    text_renderer.Load("C:\\Users\\Levi\\Downloads\\Pacman_Final\\fonts\\OCRAEXT.TTF", 24);
	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	bool startGame = false;
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Take care of all GLFW events
		glfwPollEvents();
		// Specify the color of the background
		glClearColor(0.f, 0.f, 0.f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		// Tell OpenGL which Shader Program we want to use
		
		
		level1.render_level(window, ourShader, texShader, text_rendShader, camera);
		
		
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
	}

	ourShader.Delete();
	texShader.Delete();
	text_rendShader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

        