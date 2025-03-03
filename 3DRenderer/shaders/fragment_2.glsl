#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D TEXTURE01;

void main() 
{
	// Final color
	vec4 frag = texture(TEXTURE01, TexCoord);

	FragColor = frag;
}