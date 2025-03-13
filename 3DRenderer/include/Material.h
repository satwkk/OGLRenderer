#pragma once

#include "Texture.h"
#include "glm/glm.hpp"
#include <memory>

class CShader;

class CMaterial
{
public:
	CMaterial();
	~CMaterial();

	void SetDiffuse(const std::string& texturePath, uint32_t slot);
    void SetSpecular(const std::string& texturePath, uint32_t slot);

	void Enable();
	void Disable();
    void OnRender(CShader& shader);

    static CMaterial DefaultMaterial();

	inline void SetShine(float shine) { m_fShine = shine; }
	inline CTexture& GetDiffuseMap() { return m_cDiffuse; }
	inline const float GetShine()  const { return m_fShine; }
	inline uint32_t GetDiffuseMapSlotIndex() { return m_cDiffuse.GetSlot(); }
private:
	CTexture m_cDiffuse;
	CTexture m_cSpecular;
	float m_fShine;
    glm::vec3 m_VAmbientColor;
    glm::vec3 m_VDiffuseColor; 
    glm::vec3 m_VSpecularColor; 
};
