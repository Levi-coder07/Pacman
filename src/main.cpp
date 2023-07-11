#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Pacman.h"
#include<math.h>
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include "Food.h"
#include <random>
#include <vector>
#include <cmath>
// Vertex Shader source code

double calculateDistance(double x1, double y1, double z1, double x2, double y2, double z2) {
    double deltaX = x2 - x1;
    double deltaY = y2 - y1;
    double deltaZ = z2 - z1;
    double distance = std::sqrt((deltaX * deltaX) + (deltaY * deltaY )+ (deltaZ * deltaZ));
    return distance;
}
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
	GLFWwindow* window = glfwCreateWindow(800, 800, "Trabajo Final", NULL, NULL);
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
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);



	// Create Vertex Shader Object and get its reference
	Shader shaderProgram("C:\\Users\\Levi\\Downloads\\Pacman_Final\\src\\default.vert", "C:\\Users\\Levi\\Downloads\\Pacman_Final\\src\\default.frag");


	

	int steps = 70;	// La cantidad de lineas para hacer la figura semejante al circulo que ira rotando, por conveniencia que sea un numero par
	double radiusP = 0.2; // ancho del pacman en terminos de la contextura de la ventana, siempre es positivo
	int vert_pos = 0; // Posicion del nuevo vertice a colocar para el arreglo, como solo tenemos al pacman es 0
	int index_pos = 0; // Lo mismo pero con los indices
	int vert_pos1 = 0; // Posicion del nuevo vertice a colocar para el arreglo, como solo tenemos al pacman es 0
	int index_pos1 = 0; // Lo mismo pero con los indices
	//create_pacman(vertices, 10000, indices, 21942, vert_pos, index_pos, steps, radius);
	// Generates Vertex Array Object and binds it
	double radiusB = 0.15;
    Pacman pacman(100000,100000,radiusP,40);
	pacman.createPacman(vert_pos,index_pos);
	
	
	//Pacman.createPacman(vert_pos, index_pos);
	VAO VAO1;
    
	VAO1.Bind();
    
	VBO VBO1(pacman.vertices, pacman.getSizeV() * sizeof(GL_FLOAT));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(pacman.indices,  pacman.getSizeI() * sizeof(GL_FLOAT));
     
	// Links VBO attributes such as coordinates and colors to VAO
	
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	int sizeArr = 4;
	double hol = 0.2;
	std::vector<Food> balls;
	balls.reserve(sizeArr);
	for (int i = 0; i < sizeArr ;i++) {
		Food ball1(100000,100000,radiusB,15);
		int vert_pos1 = 0; 
		int index_pos1 = 0;
		ball1.createFood(vert_pos1, index_pos1);
    	balls.push_back(ball1);
		std::cout<<balls.size();
		hol += 0.1;
	}
// Create and initialize the balls vector here
std::cout<<balls.size();
std::vector<VAO> ballVAOs;
ballVAOs.reserve(sizeArr);
std::vector<VBO> ballVBOs;
std::vector<EBO> ballEBOs;
ballVBOs.reserve(sizeArr);
ballEBOs.reserve(sizeArr);
	for ( auto& ball : balls) {
		VAO ballVAO;
		ballVAO.Bind();

		// Generate sphere vertices and indices for the ball
		
		

		VBO ballVBO(ball.vertices, ball.getSizeV() * sizeof(GL_FLOAT));
		EBO ballEBO(ball.indices,  ball.getSizeI() * sizeof(GL_FLOAT));

		// Set the vertex attribute pointers for the VAO
		ballVAO.LinkAttrib(ballVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

		// Unbind the VAO, VBO, and EBO
		ballVAO.Unbind();
		ballVBO.Unbind();
		ballEBO.Unbind();

		// Add the VAO, VBO, and EBO to their respective vectors
		ballVAOs.push_back(ballVAO);
		ballVBOs.push_back(ballVBO);
		ballEBOs.push_back(ballEBO);
	}
	//create_pacman(vertices, 10000, indices, 21942, vert_pos, index_pos, steps, radius);
	// Al terminar esta funcion, actualiza los nuevos valores de vertpos e indexpos para colocar otros vertices e indices


	// Create reference containers for the Vartex Array Object, the Vertex Buffer Object, and the Element Buffer Object
	std::srand(time(NULL));
	 std::random_device rd;
    std::mt19937 gen(rd());
    
    // Create a uniform real distribution
    std::uniform_real_distribution<float> dis(0.0, 1.0);
	std::vector<glm::mat4> translations;
	for(int i = 0;i<sizeArr;i++){
		float randomNum = dis(gen);
		std::cout<<randomNum<<std::endl;
		translations.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(randomNum, randomNum, 0)));
		balls[i].center_x = randomNum;
		balls[i].center_y =  randomNum;
		balls[i].center_z = 0;
	}
	
	double factor = 1;
	  float translationX = -0.0f;
	 bool reverseDirection = false;
     float translationSpeed = 0.1f;
    const float translationLimit = 1.f;
	glm::mat4 prev_transform = glm::mat4(1.0f);
	 float previousTime = glfwGetTime();
	 float sumX = 0.0f;
float sumY = 0.0f;
float sumZ = 0.0f;

    glEnable(GL_DEPTH_TEST); 
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		// Tell OpenGL which Shader Program we want to use
		 
		// Bind the VAO so OpenGL knows to use it
		shaderProgram.Activate();
		
		
        double  timeValue = glfwGetTime();
        /*int vertexColorLocation = glGetUniformLocation(shaderProgram.ID, "ourColor");
        glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);*/


         // create transformations
		glm::mat4 transform = prev_transform; // make sure to initialize matrix to identity matrix first

        if (glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
        {
            transform = glm::rotate(transform, 0.01f, glm::vec3(1.0, 0.0, 0.0));
        }
          if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        transform = glm::translate(transform, glm::vec3(0.0f, 0.01f, 0.0f));
        pacman.center_y += 0.01f; // Update center's y-coordinate
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        transform = glm::translate(transform, glm::vec3(0.0f, -0.01f, 0.0f));
        pacman.center_y -= 0.01f; // Update center's y-coordinate
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        transform = glm::translate(transform, glm::vec3(0.01f, 0.0f, 0.0f));
        pacman.center_x += 0.01f; // Update center's x-coordinate
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        transform = glm::translate(transform, glm::vec3(-0.01f, 0.0f, 0.0f));
       pacman.center_x -= 0.01f; // Update center's x-coordinate
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.01f));
        pacman.center_z += 0.01f; // Update center's z-coordinate
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, -0.01f));
        pacman.center_z -= 0.01f; // Update center's z-coordinate
    }
		
		prev_transform = transform;
	
		float currentTime = glfwGetTime();

    
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

      	view = glm::translate(view, glm::vec3(.0f, -0.0f, -3.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)800.0f / 800.0f, 0.1f, 100.0f);
   		 int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
		    unsigned int transformLoc1 = glGetUniformLocation(shaderProgram.ID, "transform");
        glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(transform));
		
 
    //glm::mat4 transform2 = glm::translate(transform, glm::vec3(translationX, 0.0f, 0.0f));
		VAO1.Bind();
		
    
		pacman.draw(shaderProgram);
        // draw our first triangle
      // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		// Draw primitives, number of indices, datatype of indices, index of indices
		
    // Bind the VAO so OpenGL knows to use it

    	for (int i = 0; i < sizeArr; ++i) {
			ballVAOs[i].Bind();
			
			// Update the transformation matrix uniform in the shader
				 /*view = glm::translate(view, glm::vec3(.0f, -0.0f, -3.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)800.0f / 800.0f, 0.1f, 100.0f);
   	 int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));*/
				glm::mat4 transform3 = glm::translate(translations[i], glm::vec3(0.0f, 0.f, 0.0f));
		 	 	unsigned int transformLoc2 = glGetUniformLocation(shaderProgram.ID, "transform");
        		glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(transform3));
			
		
			// Render the ball
			if(!balls[i].isEaten){
				double dist = calculateDistance(balls[i].center_x,balls[i].center_y,balls[i].center_z,pacman.center_x,pacman.center_y,pacman.center_z);
				if(dist>=radiusB+radiusP){
					
					balls[i].draw(shaderProgram);
					ballVAOs[i].Unbind();
				}else{
						std::cout<<"COLISION"<<std::endl;
				}
			}
			
			
	}
		
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	for(auto vaos:ballVAOs){
		vaos.Delete();
	}
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}

        