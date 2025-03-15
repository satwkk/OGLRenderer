#version 330 core

// =====================
// STRUCTS
// =====================
struct Material 
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D normalMap;
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
in mat3 TBN;
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
	// Get the world normal based on normal map is set or not
	vec3 normalMapValue = texture(material.normalMap, TexCoord).rgb;
    normalMapValue = normalMapValue * 2.0 - 1.0;
	vec3 worldNormal = normalize(TBN * normalMapValue);

	// Diffuse reflection
	vec3 directionToLight = normalize(light.position - FragmentWorldPosition);
	float diffuseFactor = max(dot(worldNormal, directionToLight), 0.0);

	// Specular reflection
	vec3 reflectedLight = reflect(-directionToLight, worldNormal);
	vec3 directionToCamera = normalize(uCameraPosition - FragmentWorldPosition);
	float specularFactor = pow(max(dot(directionToCamera, reflectedLight), 0.0), material.shine);

    // Diffuse light
    vec3 diffuseTextureColor = texture(material.diffuse, TexCoord).rgb;
	bool isDiffuseTextureSet = length(diffuseTextureColor) > 0.01;
    vec3 diffuseColor = isDiffuseTextureSet ? diffuseTextureColor : material.diffuseColor;

    // Specular light
    vec3 specularTextureColor = texture(material.specular, TexCoord).rgb;
	bool isSpecularTextureSet = length(specularTextureColor) > 0.01;
    vec3 specularColor = isSpecularTextureSet ? specularTextureColor : material.specularColor;

    // Final calculations
	vec3 ambient = light.ambient * material.ambientColor * diffuseColor;
	vec3 diffuseLight = light.diffuse * diffuseFactor * diffuseColor;
	vec3 specularLight = light.specular * specularFactor * specularColor;

	FragColor = vec4(ambient + diffuseLight + specularLight, 1.0);
}
