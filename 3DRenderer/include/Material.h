#pragma once

#include <initializer_list>

#include "Texture.h"

class Material
{
public:
	Material() = default;
	~Material() = default;

	void SetDiffuse(const std::string& texturePath);
	void SetSpecular(const std::string& texturePath);

	void Enable();
	void Disable();

	inline void SetShine(float shine) { m_Shine = shine; }

	inline const Texture& GetDiffuseMap() const { return m_Diffuse; }
	inline const Texture& GetSpecularMap() const { return m_Specular; }
	inline const float GetShine() const { return m_Shine; }
private:
	Texture m_Diffuse;
	Texture m_Specular;
	float m_Shine;
};