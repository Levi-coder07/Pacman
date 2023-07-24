#version 330 core
in vec2 TexCoords;
out vec4 color;
uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
    float glyphShape =  texture(text, TexCoords).r;
    if (glyphShape< 0.5f)
        discard;
    color = vec4(textColor, 1.0) ;
}
