#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;

uniform mat4 uVPMatrix;
uniform mat4 uModelMatrix;

out vec2 TexCoord;
out mat3 TBN;
out vec3 FragmentWorldPosition;

void main() 
{
    TexCoord = aTexCoord;
    FragmentWorldPosition = vec3(uModelMatrix * vec4(aPos, 1.0));

    // Calculate TBN matrix
    mat3 transposeInverseModelMatrix = mat3(transpose(inverse(uModelMatrix)));
    vec3 T = normalize(transposeInverseModelMatrix * aTangent);
    vec3 N = normalize(transposeInverseModelMatrix * aNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    TBN = mat3(T, B, N);

    gl_Position = uVPMatrix * uModelMatrix * vec4(aPos, 1.0);
}