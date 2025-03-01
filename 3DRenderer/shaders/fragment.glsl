#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D TEXTURE01;

void main() 
{
    FragColor = texture(TEXTURE01, TexCoord);
}