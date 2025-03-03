#include "Material.h"

void Material::SetDiffuse(const std::string& texturePath)
{
	m_Diffuse = Texture(texturePath, 0);
}

void Material::SetSpecular(const std::string& texturePath)
{
	m_Specular = Texture(texturePath, 1);
}

void Material::Enable()
{
	m_Diffuse.Bind();
	m_Specular.Bind();
}

void Material::Disable()
{
	m_Diffuse.UnBind();
	m_Specular.UnBind();
}
