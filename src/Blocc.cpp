#include "Blocc.h"

Blocc::Blocc(double size_, float angle, float x, float y)
{
    this->size = size_;
    this->centerPoint = glm::vec3(0.f,0.f,0.f);
    this->vertices.resize(24);
    this->indices.resize(36);

    this->position = glm::vec3(0.f);
    this->rotation = glm::vec3(0.f);
    this->scale = glm::vec3(1.f);


    // Cuadrado superior
    this->vertices[0].pos = glm::vec3(size + x, size + y, size);//
    this->vertices[1].pos = glm::vec3(- size + x, size + y, size); //
    this->vertices[2].pos = glm::vec3(size + x, -size + y, size); //
    this->vertices[3].pos = glm::vec3(- size + x, -size + y, size);//

    // Cuadrado lateral
    this->vertices[4].pos = glm::vec3(- size + x, size + y, size);
    this->vertices[5].pos = glm::vec3(size + x, size + y, size);
    this->vertices[6].pos = glm::vec3(- size + x, size + y, -size); //
    this->vertices[7].pos = glm::vec3(size + x, size + y, -size); //

    // Cuadrado lateral 2
    this->vertices[8].pos = glm::vec3(size + x, -size + y, size); 
    this->vertices[9].pos = glm::vec3(- size + x, -size + y, size);
    this->vertices[10].pos = glm::vec3(size + x, -size + y, -size); //
    this->vertices[11].pos = glm::vec3(-size + x, -size + y, -size);//

    // Cuadrado lateral 3
    this->vertices[12].pos = glm::vec3(- size + x, size + y, size); 
    this->vertices[13].pos = glm::vec3(- size + x, -size + y, size);
    this->vertices[14].pos = glm::vec3(- size + x, size + y, -size); 
    this->vertices[15].pos = glm::vec3(-size + x, -size + y, -size);

    // Cuadrado lateral 4
    this->vertices[16].pos = glm::vec3(size + x, size + y, size);
    this->vertices[17].pos = glm::vec3(size + x, -size + y, size); 
    this->vertices[18].pos = glm::vec3(size + x, size + y, -size); 
    this->vertices[19].pos = glm::vec3(size + x, -size + y, -size); 

    // Cuadrado inferior
    this->vertices[20].pos = glm::vec3(size + x, size + y, -size); 
    this->vertices[21].pos = glm::vec3(- size + x, size + y, -size); 
    this->vertices[22].pos = glm::vec3(size + x, -size + y, -size); 
    this->vertices[23].pos = glm::vec3(-size + x, -size + y, -size);
    
    for (int i = 0; i < 4; i++)
    {   
        
        this->centerPoint.x = this->centerPoint.x + this->vertices[i].pos.x;
         this->centerPoint.y = this->centerPoint.y + this->vertices[i].pos.y;
          this->centerPoint.z = this->centerPoint.z + this->vertices[i].pos.z;
    }
    for (int i = 6; i < 12; i+=4)
    {   
        
        
        this->centerPoint.x = this->centerPoint.x + this->vertices[i].pos.x;
         this->centerPoint.y = this->centerPoint.y + this->vertices[i].pos.y;
          this->centerPoint.z = this->centerPoint.z + this->vertices[i].pos.z;
        //std::cout<<this->centerPoint.x<<std::endl;
          this->centerPoint.x = this->centerPoint.x + this->vertices[i+1].pos.x;
         this->centerPoint.y = this->centerPoint.y + this->vertices[i+1].pos.y;
          
          this->centerPoint.z = this->centerPoint.z + this->vertices[i+1].pos.z;

         //std::cout<<this->vertices[i].pos.x<<" "<<this->vertices[i+1].pos.x<<std::endl;
    }

    //this->centerPoint.x = this->centerPoint.x + this->vertices[6].pos.x+ this->vertices[7].pos.x+ this->vertices[10].pos.x+ this->vertices[11].pos.x;
    //this->centerPoint.y = this->centerPoint.y + this->vertices[6].pos.y+ this->vertices[7].pos.y+ this->vertices[10].pos.y+ this->vertices[11].pos.y;
    
    if (std::abs(this->centerPoint.z) < 1e-6) {
        this->centerPoint.z = 0.0;
}
    // this->centerPoint.z = this->centerPoint.z + this->vertices[6].pos.z;
    this->centerPoint = this->centerPoint / 8.f;
   
    //+ this->vertices[7].pos.z+ this->vertices[10].pos.z+ this->vertices[11].pos.z
    //this->centerPoint.z = 0;
        
    
    /*std::cout<<this->centerPoint.x<<" ";
    std::cout<<this->centerPoint.y<<" ";
    std::cout<<this->centerPoint.z<<std::endl;*/
    for (int i = 0; i < 24; i++)
    {
        this->vertices[i].color = glm::vec3(1.0f, 1.0f, 1.0f);
        if (i % 4 == 0)
        {
            this->vertices[i].tex_coord = glm::vec2(0.0f, 0.0f);
        }
        else if (i % 4 == 1)
        {
            this->vertices[i].tex_coord = glm::vec2(1.0f, 0.0f);
        } 
        else if (i % 4 == 2)
        {
            this->vertices[i].tex_coord = glm::vec2(0.0f, 1.0f);
        }
        else 
        {
            this->vertices[i].tex_coord = glm::vec2(1.0f, 1.0f);
        }
    }

    this->indices =
    {
        0, 1, 2,
        1, 2, 3,
        4, 5, 6,
        5, 6, 7,
        8, 9, 10,
        9, 10, 11,
        12, 13, 14,
        13, 14, 15,
        16, 17, 18,
        17, 18, 19,
        20, 21, 22, 
        21, 22, 23
    };

    vao.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    VBO vbo(vertices);
    // Generates Element Buffer Object and links it to indices
    EBO ebo(indices);
    // Links VBO attributes such as coordinates and colors to VAO
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));

    // Unbind all to prevent accidentally modifying them
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
}

void Blocc::draw(Shader &shaderProgram) 
{
    shaderProgram.use();
    
    shaderProgram.setInt("ourTexture", 0);
    
    // create transformations
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);

    shaderProgram.setMat4("model", model);

    vao.Bind();


    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)(0));

}