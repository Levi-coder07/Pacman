#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;
uniform mat4 projection;
uniform mat4 model;
uniform mat4 camMatrix;
void main()
{
    if(vertex.xy.y>10){
        gl_Position = projection* vec4(vertex.xy, 0.0f, 1.0f);
        TexCoords = vertex.zw;
    }else{
        gl_Position = camMatrix * model* vec4(vertex.xy, 0.25f, 1.0f);
        TexCoords = vertex.zw;
    }
    
   
}