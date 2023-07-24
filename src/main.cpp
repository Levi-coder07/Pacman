#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <time.h>

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

const char * vertex_texture_shader_file = "C:\\Users\\Levi\\Downloads\\Pacman_Final\\src\\texshader.vert";
const char * fragment_texture_shader_file = "C:\\Users\\Levi\\Downloads\\Pacman_Final\\src\\texshader.frag";

const char * vertex_text_shader_file = "C:\\Users\\Levi\\Downloads\\Pacman_Final\\src\\text_shader.vert";
const char * fragment_text_shader_file = "C:\\Users\\Levi\\Downloads\\Pacman_Final\\src\\text_shader.frag";
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
double calculate_distance(double x1, double y1, double z1, double x2, double y2, double z2);

int main()
{
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
	Shader texShader(vertex_texture_shader_file, fragment_texture_shader_file);
	
	Shader text_rendShader(vertex_text_shader_file,fragment_text_shader_file);
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
    text_rendShader.use();
    glUniformMatrix4fv(glGetUniformLocation(text_rendShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
/*
	int steps = 70;	// La cantidad de lineas para hacer la figura semejante al circulo que ira rotando, por conveniencia que sea un numero par
	double radiusP = 0.3; // ancho del pacman en terminos de la contextura de la ventana, siempre es positivo
	double radiusB = 0.05;

	Pacman pacman(0.2,40);

	pacman.rotation.x = 90.f;
*/
	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 2.0f, 3.f));
/*	Ghost ghost(0.18f, 22);
	
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
	 {"#....##.##...#"},
	 {"#............#"},
	 {"#..........#.#"},
	 {"#..........#.#"},
	 {"#.....#.####.#"},
	 {"#..........#.#"},
	 {"#..........#.#"},
	 {"##############"},
	};	

	Level level1(glm::vec3(0.0f, 0.0f, 0.0f), matrix);
	/*std::vector<Food*> balls;
	
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].length(); j++)
		{
			if (matrix[i][j] == '.')
			{
				balls.push_back(new Food(0.05, 20, j * 0.2f * 2, i * 0.2f * 2));
			}
		}
	}

	int sizeArr = balls.size();

	std::vector<Texture> textures = { Texture("C:\\7mo Semestre\\Computacion Grafica\\TrabajoFinal\\Textures\\pared.jpg", 0 ,GL_RGB, GL_UNSIGNED_BYTE)};

	Maze map(matrix, 0.2f, textures);
	

	ghost.rotation.x = 180.f;

	ghost.position = glm::vec3(-0.7f,-0.7f, 0.0f);
	*/
	// Main while loop
	std::string points ;
	TextRenderer text_renderer= TextRenderer(800,800);
    text_renderer.Load("C:\\Users\\Levi\\Downloads\\Pacman_Final\\fonts\\OCRAEXT.TTF", 24);
	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
	while (!glfwWindowShouldClose(window))
	{
		// Take care of all GLFW events
		glfwPollEvents();
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		// Tell OpenGL which Shader Program we want to use
		
		//text_renderer.RenderText("This is sample text", 15.0f, 15.0f, 1.5f,text_rendShader, glm::vec3(0.5, 0.8f, 0.2f));
		level1.render_level(window, ourShader, texShader, camera,text_rendShader);

/*
		pacman.updateInput(window);
		// Rendering pacman
		pacman.draw(ourShader);
		ghost.draw(ourShader);
		map.draw(texShader);

		for (int i = 0; i < sizeArr; i++) 
		{
			// Render the ball
			if (!balls[i]->is_eaten)
			{
				double dist = calculate_distance(balls[i]->position.x,balls[i]->position.y,balls[i]->position.z,pacman.position.x,pacman.position.y,pacman.position.z);
				if (dist >= 0.25)
				{
					balls[i]->draw(ourShader);
				}
				else
				{
					std::cout << "COLISION" << std::endl;
					balls[i]->is_eaten = true;
				}
			}
		}
*/		
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


double calculate_distance(double x1, double y1, double z1, double x2, double y2, double z2) {
    double deltaX = x2 - x1;
    double deltaY = y2 - y1;
    double deltaZ = z2 - z1;
    double distance = std::sqrt((deltaX * deltaX) + (deltaY * deltaY )+ (deltaZ * deltaZ));
    return distance;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

        