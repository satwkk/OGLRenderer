#version 330 core

// =====================
// STRUCTS
// =====================
struct Material 
{
	sampler2D diffuse;
	sampler2D specular;
    vec3 diffuseColor;
    vec3 specularColor;
    vec3 ambientColor;
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
	// Diffuse reflection
	vec3 norm = normalize(Normal);
	vec3 directionToLight = normalize(light.position - FragmentWorldPosition);
	float diffuseFactor = max(dot(norm, directionToLight), 0.0);

	// Specular reflection
	vec3 reflectedLight = reflect(-directionToLight, norm);
	vec3 directionToCamera = normalize(uCameraPosition - FragmentWorldPosition);
	float specularFactor = pow(max(dot(directionToCamera, reflectedLight), 0.0), material.shine);

    // Diffuse light
    vec3 diffuseTextureColor = texture(material.diffuse, TexCoord).rgb;
    vec3 diffuseColor = mix(material.diffuseColor, diffuseTextureColor, step(0.01, length(diffuseTextureColor)));

    // Specular light
    vec3 specularTextureColor = texture(material.specular, TexCoord).rgb;
    vec3 specularColor = mix(material.specularColor, specularTextureColor, step(0.01, length(specularTextureColor)));

    // Final calculations
	vec3 ambient = light.ambient * material.ambientColor * diffuseColor;
	vec3 diffuseLight = light.diffuse * diffuseFactor * diffuseColor;
	vec3 specularLight = light.specular * specularFactor * specularColor;

	FragColor = vec4(ambient + diffuseLight + specularLight, 1.0);
}
