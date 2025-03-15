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
    void SetNormalMap(const std::string& texturePath, uint32_t slot);

	inline void SetAmbientColor(const glm::vec3& sColor) { m_VAmbientColor = sColor; }
	inline void SetDiffuseColor(const glm::vec3& sColor) { m_VDiffuseColor = sColor; }
    inline void SetSpecularColor(const glm::vec3& sColor) { m_VSpecularColor = sColor; }

	void Enable();
	void Disable();
    void OnRender(CShader& shader);

    static CMaterial DefaultMaterial();

	inline void SetShine(float shine) { m_fShine = shine; }
	inline CTexture& GetDiffuseMap() { return m_CDiffuse; }
	inline const float GetShine()  const { return m_fShine; }
	inline uint32_t GetDiffuseMapSlotIndex() { return m_CDiffuse.GetSlot(); }
private:
	CTexture m_CDiffuse;
	CTexture m_CSpecular;
	CTexture m_CNormalMap;
	float m_fShine;
    glm::vec3 m_VAmbientColor;
    glm::vec3 m_VDiffuseColor; 
    glm::vec3 m_VSpecularColor; 
    uint32_t m_uAvailableSlot;
};
