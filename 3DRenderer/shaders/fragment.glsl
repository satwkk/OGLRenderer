#version 330 core

// =====================
// STRUCTS
// =====================
struct Material 
{
	sampler2D diffuse;
	float shine;
};

struct Light 
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// =====================
// IN PARAMS
// =====================
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragmentWorldPosition;


// =====================
// OUT PARAMS
// =====================
out vec4 FragColor;

// =====================
// UNIFORMS
// =====================
uniform vec3 uCameraPosition;
uniform Material material;
uniform Light light;

void main() 
{
	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 directionToLight = normalize(light.position - FragmentWorldPosition);
	float diffuseFactor = max(dot(norm, directionToLight), 0.0);

	// Specular
	// vec3 reflectedLight = reflect(-directionToLight, norm);
	// vec3 directionToCamera = normalize(uCameraPosition - FragmentWorldPosition);
	// float specular = pow(max(dot(directionToCamera, reflectedLight), 0.0), material.shine);

	vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;

	vec4 diffuseTexture = texture(material.diffuse, TexCoord);
	if (diffuseTexture.a < 0.5) 
		discard;

	vec3 diffuseLight = light.diffuse * diffuseFactor * diffuseTexture.rgb;
	// vec3 specularLight = light.specular * specular * texture(material.specular, TexCoord).rgb;
	
	// Final color
	// FragColor = vec4(ambient + diffuseLight + specularLight, 1.0);
	FragColor = vec4(ambient + diffuseLight, diffuseTexture.a);
}