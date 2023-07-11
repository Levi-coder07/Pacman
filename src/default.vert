#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec2 aTexCoord;

// Outputs the color for the Fragment Shader
out vec3 color;
out vec2 TexCoord;
// Controls the scale of the vertices
uniform mat4 scale;
uniform mat4 transform;
// Uniform color variable

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    // Outputs the positions/coordinates of all vertices
    gl_Position = proj*view* transform * vec4(aPos, 1.0);
   
}