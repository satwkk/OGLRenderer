#pragma once

#include <initializer_list>
#include <memory>
#include "Texture.h"
#include "Shader.h"

class Material
{
public:
	Material();
	~Material();

	void SetDiffuse(const std::string& texturePath, uint32_t slot);

	void Enable();
	void Disable();

	inline void SetShine(float shine) { m_Shine = shine; }
	inline Texture& GetDiffuseMap() { return m_Diffuse; }
	inline float GetShine() { return m_Shine; }
	inline uint32_t GetDiffuseMapSlotIndex() { return m_Diffuse.GetSlot(); }
private:
	Texture m_Diffuse;
	Texture m_Ambient;
	float m_Shine;
};