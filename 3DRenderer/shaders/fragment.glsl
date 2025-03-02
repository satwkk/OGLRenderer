#version 330 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragmentWorldPosition;

out vec4 FragColor;

uniform vec3 uLightColor;
uniform vec3 uLightPos;
uniform vec3 uCameraPosition;

uniform sampler2D TEXTURE01;

void main() 
{
	vec3 objectColor = texture(TEXTURE01, TexCoord).rgb;

	// Ambient
	float ambientStrength = 0.1;
	vec3 ambient = uLightColor * ambientStrength;

	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 directionToLight = normalize(uLightPos - FragmentWorldPosition);
	float diffuse = max(dot(norm, directionToLight), 0.0);
	vec3 diffuseLight = diffuse * uLightColor;

	// Specular
	vec3 reflectedLight = reflect(-directionToLight, norm);
	vec3 directionToCamera = normalize(uCameraPosition - FragmentWorldPosition);
	float specular = max(pow(dot(reflectedLight, directionToCamera), 32), 0.0);
	vec3 specularLight = specular * uLightColor;
	
	// Final color
	vec3 result = (ambient + diffuseLight + specularLight) * objectColor;
	FragColor = vec4(result, 1.0);
}