#pragma once

#include "Texture.h"
#include "glm/glm.hpp"
#include <memory>

class Shader;

class Material
{
public:
	Material();
	~Material();

	void SetDiffuse(const std::string& texturePath, uint32_t slot);
    void SetSpecular(const std::string& texturePath, uint32_t slot);

	void Enable();
	void Disable();
    void OnRender(const std::shared_ptr<Shader>& shader);

    static Material DefaultMaterial();

	inline void SetShine(float shine) { m_Shine = shine; }
	inline Texture& GetDiffuseMap() { return m_Diffuse; }
	inline float GetShine() { return m_Shine; }
	inline uint32_t GetDiffuseMapSlotIndex() { return m_Diffuse.GetSlot(); }
private:
	Texture m_Diffuse;
	Texture m_Specular;
	float m_Shine;
    glm::vec3 m_AmbientColor;
    glm::vec3 m_DiffuseColor; 
    glm::vec3 m_SpecularColor; 
};
