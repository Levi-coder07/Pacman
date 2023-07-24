#include "Level.h"

Level::Level(glm::vec3 start_pos, std::vector<std::string> matrix)
{
	std::vector<Texture> textures = { Texture("C:\\Users\\Levi\\Downloads\\Pacman_Final\\Textures\\pared.jpg", 0 ,GL_RGB, GL_UNSIGNED_BYTE)};
   
   	text_renderer = new TextRenderer(800,800);
    this->text_renderer->Load("C:\\Users\\Levi\\Downloads\\Pacman_Final\\fonts\\OCRAEXT.TTF", 24);
	std::cout<<"E";
    this->map = new Maze(matrix, 0.2, textures);
    this->pacman = new Pacman(0.2, 40);
    this->pacman->position = start_pos;
	this->pacman->rotation.x = 90.f;

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j] == '.')
            {
                food_vector.push_back(new Food(0.05, 20, j * map->map_size * 2, i * map->map_size * 2));
            }
        }
    }
}

void Level::render_level(GLFWwindow * window, Shader & color_shader, Shader & texture_shader, Camera & camera,Shader&text_shader)
{
    camera.process_input(window);
	camera.updateMatrix(45.f, 0.1f, 100.f);

	camera.Matrix(color_shader, "camMatrix");
	camera.Matrix(texture_shader, "camMatrix");
	camera.Matrix(text_shader,"camMatrix");
	
	this->pacman->updateInput(window);

    this->pacman->draw(color_shader);
    this->map->draw(texture_shader);

    for (int i = 0; i < food_vector.size(); i++) 
		{
			// Render the ball
			if (!food_vector[i]->is_eaten)
			{
				double dist = glm::distance(food_vector[i]->position, pacman->position);
				if (dist >= 0.25)
				{
					food_vector[i]->draw(color_shader);
				}
				else
				{
					
					std::cout << "COLISION" << std::endl;
					food_vector[i]->is_eaten = true;
				}
			}
			else{
				text_renderer->RenderText( "GAME OVER", 1.0f, 50.0f, 5.0f,text_shader, glm::vec3(1.0f, .0f, 0.0f));
			}
		}
		
}