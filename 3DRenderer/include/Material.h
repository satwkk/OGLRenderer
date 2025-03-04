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

	void SetDiffuse(const std::string& texturePath);
	void SetSpecular(const std::string& texturePath);
	void SetAmbient(const std::string& texturePath);

	void Enable();
	void Disable();

	inline void SetShine(float shine) { m_Shine = shine; }

	inline const Texture& GetDiffuseMap() const { return m_Diffuse; }
	inline const Texture& GetSpecularMap() const { return m_Specular; }
	inline const float GetShine() const { return m_Shine; }
private:
	std::shared_ptr<Shader> m_Shader;
	Texture m_Diffuse;
	Texture m_Specular;
	Texture m_Ambient;
	float m_Shine;
};