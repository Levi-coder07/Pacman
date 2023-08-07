#include "Level.h"

Level::Level(std::vector<std::string> matrix, Camera & camera)
{
	std::vector<Texture> textures = { Texture("C:\\Users\\Levi\\Downloads\\Pacman_final\\Textures\\pared.jpg", 0 ,GL_RGB, GL_UNSIGNED_BYTE)};
    
	text_renderer = new TextRenderer(1200,1000);
    this->text_renderer->Load("C:\\Users\\Levi\\Downloads\\Pacman_final\\fonts\\OCRAEXT.TTF", 24);

    this->map = new Maze(matrix, 0.3, textures);
    this->pacman = new Pacman(0.12, 40);
	this->pacman->rotation.x = 90.f;

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j] == '.')
            {
                food_vector.push_back(new Food(0.05, 20, i * map->map_size * 2, j * map->map_size * 2));
            }
			else if (matrix[i][j] == '@')
            {
                ghosts.push_back(new Ghost(0.15, 18, i * map->map_size * 2, j * map->map_size * 2, map->map_size));
            }
			else if (matrix[i][j] == '*')
			{
				cherries.push_back(new Cherry(0.15, 18, i * map->map_size * 2, j * map->map_size * 2));
			}
			else if (matrix[i][j] == 'o')
			{
				pacman->position.x = i * map->map_size * 2;
				pacman->position.y = j * map->map_size * 2;
				start_pos = glm::vec3(i * map->map_size * 2, j * map->map_size * 2, 0.0f);
				camera.position.x += i * map->map_size * 2;
				camera.position.y += j * map->map_size * 2;
			}
        }
    }
}

void Level::render_level(GLFWwindow * window, Shader & color_shader, Shader & texture_shader, Shader&text_shader, Camera & camera)
{
	camera.updateMatrix(45.f, 0.1f, 100.f);

	camera.Matrix(color_shader, "camMatrix");
	camera.Matrix(texture_shader, "camMatrix");
	camera.Matrix(text_shader,"camMatrix");

	if (!start_game)
	{
		camera.position.x = 0.0;
		camera.position.y = -2.5f;
		//camera.process_input(window);
		glDepthMask(GL_FALSE);
		text_renderer->RenderText("PACMAN 3D",-1.55,0.3, 0.023f,text_shader, glm::vec3(0.0f, 1.0f, 0.0f));
		text_renderer->RenderText("PRESS P TO",-1.15,-0.2, 0.015f,text_shader, glm::vec3(1.0f, .0f, 0.0f));
		text_renderer->RenderText("START GAME",-1.15,-0.7, 0.015f,text_shader, glm::vec3(1.0f, .0f, 0.0f));
		text_renderer->RenderText("INSTRUCTIONS",-0.95, -1.2, 0.010f,text_shader, glm::vec3(1.0f, .0f, 0.0f));
		text_renderer->RenderText("MADE BY LEVI , MOISES , EDSON - UNSA ", 15.f, 15.0f, 1.3f,text_shader, glm::vec3(1.0f, 1.0f, 1.0f));
		glDepthMask(GL_TRUE);
		if(glfwGetKey(window,GLFW_KEY_P)==GLFW_PRESS)
		{
			start_game=true;
		}
		if(glfwGetKey(window,GLFW_KEY_I)==GLFW_PRESS)
		{
			instruccion = true;
			start_game = true;
		}
	}
	else if (instruccion)
	{
		//camera.process_input(window);
		glDepthMask(GL_FALSE);
		start_game = true;
		text_renderer->RenderText("PRESS A -> LEFT",-1.3, 0.3, 0.012f,text_shader, glm::vec3(1.0f, .0f, 0.0f));
		text_renderer->RenderText("PRESS D -> RIGHT",-1.3, -0.2, 0.012f,text_shader, glm::vec3(1.0f, .0f, 0.0f));
		text_renderer->RenderText("PRESS W -> UP",-1.3, -0.7, 0.012f,text_shader, glm::vec3(1.0f, .0f, 0.0f));
		text_renderer->RenderText("PRESS S -> DOWN",-1.3, -1.2, 0.012f,text_shader, glm::vec3(1.0f, .0f, 0.0f));
		glDepthMask(GL_TRUE);
		if(glfwGetKey(window,GLFW_KEY_L)==GLFW_PRESS)
		{
			instruccion=false;
			start_game=true;
			
		}
	}
	else if(game_over)
	{
		//camera.process_input(window);
		camera.position.x = 0.5;
		camera.position.y = -2.5f;
		text_renderer->RenderText("GAME", -0.8, 0.4f, 0.035f,text_shader, glm::vec3(1.0f, .0f, 0.0f));
		text_renderer->RenderText("OVER!", -0.8, -1.1f, 0.035f,text_shader, glm::vec3(1.0f, .0f, 0.0f));
		
		text_renderer->RenderText("PRESS R TO RESTART!", -0.4, -1.3f, 0.005f,text_shader, glm::vec3(1.0f, .0f, 0.0f));
		if(glfwGetKey(window,GLFW_KEY_R)==GLFW_PRESS){
			instruccion=false;
			start_game=false;
			game_over=false;
			for (int i = 0; i < food_vector.size(); i++)
			{
				food_vector[i]->is_eaten = false;
			}
			for (int i = 0; i < cherries.size(); i++)
			{
				cherries[i]->is_eaten = false;
			}
			pacman->pointCounter = 0;
			pacman->position = start_pos;
			camera.position.x = pacman->position.x;
			camera.position.y = pacman->position.y - 3.0f;
		}
	}else if(pacman->pointCounter>=20){
		camera.position.x = 0.5;
		camera.position.y = -2.5f;
		text_renderer->RenderText("CONGRATS", -0.8, 0.4f, 0.025f,text_shader, glm::vec3(1.0f, .0f, 0.0f));
		text_renderer->RenderText("YOU WIN!", -0.8, -1.1f, 0.025f,text_shader, glm::vec3(1.0f, .0f, 0.0f));
		
		text_renderer->RenderText("PRESS R TO CONTINUE!", -0.4, -1.3f, 0.005f,text_shader, glm::vec3(1.0f, .0f, 0.0f));
		if(glfwGetKey(window,GLFW_KEY_R)==GLFW_PRESS){
			instruccion=false;
			start_game=false;
			game_over=false;
			for (int i = 0; i < food_vector.size(); i++)
			{
				food_vector[i]->is_eaten = false;
			}
			for (int i = 0; i < cherries.size(); i++)
			{
				cherries[i]->is_eaten = false;
			}
			pacman->pointCounter = 0;
			pacman->position = start_pos;
			camera.position.x = pacman->position.x;
			camera.position.y = pacman->position.y - 3.0f;
		}
	}
	else
	{
		camera.position.x = pacman->position.x;
		camera.position.y = pacman->position.y - 3.0f;
		this->pacman->updateInput(window, map->blocks, map->map_size, camera);

		this->pacman->draw(color_shader);
		this->map->draw(texture_shader);

		std::string label = "POINTS : " + std::to_string(pacman->pointCounter);
		glDepthMask(GL_FALSE); // Don't write into the depth buffer
		text_renderer->RenderText(label, 15.f, 15.0f, 2.5f,text_shader, glm::vec3(1.0f, .0f, 0.0f));
		glDepthMask(GL_TRUE); // Re-enable writing to the depth buffer


		for (int i = 0; i < food_vector.size(); i++) 
		{
			// Render the ball
			if (!food_vector[i]->is_eaten)
			{
				double dist = glm::distance(food_vector[i]->position, pacman->position);
				if (dist >= 0.05 + 0.2 * pacman->scale.x)
				{
					food_vector[i]->draw(color_shader);
				}
				else
				{
					std::cout << "COLISION" << std::endl;
					pacman->pointCounter++;
					food_vector[i]->is_eaten = true;
				}
			}
		}

		for (int i = 0; i < cherries.size(); i++)
		{
			if (!cherries[i]->is_eaten)
			{
				double dist = glm::distance(cherries[i]->position, pacman->position);
				if (dist >= 0.35)
				{
					cherries[i]->draw(color_shader);
				}
				else
				{
					std::cout << "COLISION" << std::endl;
					pacman->activate_powerup();
					cherries[i]->is_eaten = true;
				}
			}
		}

		for (int i = 0; i < ghosts.size(); i++)
		{
			ghosts[i]->move(*(this->map), this->map->map_size);
			
			double distancia = glm::distance(ghosts[i]->position,pacman->position);
			if(!ghosts[i]->touched){
				if(pacman->in_powerup){
					
					if (distancia <= pacman->radius + ghosts[i]->radius)
					{
						pacman->pointCounter += 10;
						std::cout << "COLISION CON POWERUP" << std::endl;
						std::cout << "COLISION CON GHOST" << std::endl;
						ghosts[i]->touched = true;

					}
					else	{
						ghosts[i]->draw(color_shader);
					}
				}
				else if (distancia <= pacman->radius + ghosts[i]->radius)
				{
					
					std::cout << "COLISION CON GHOST" << std::endl;
					game_over = true;
				}
				else{
					ghosts[i]->draw(color_shader);
				}
			}
		}
	}
}