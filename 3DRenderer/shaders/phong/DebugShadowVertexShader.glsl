#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 uModelMatrix;
uniform mat4 uVPMatrix;

void main() 
{
    gl_Position = uVPMatrix * uModelMatrix * vec4(aPos, 1.0);
}
