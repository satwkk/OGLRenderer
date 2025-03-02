#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 uVPMatrix;
uniform mat4 uModelMatrix;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragmentWorldPosition;

void main() 
{
    TexCoord = aTexCoord;
    Normal = mat3(transpose(inverse(uModelMatrix))) * aNormal;
    FragmentWorldPosition = vec3(uModelMatrix * vec4(aPos, 1.0));
    gl_Position = uVPMatrix * uModelMatrix * vec4(aPos, 1.0);
}