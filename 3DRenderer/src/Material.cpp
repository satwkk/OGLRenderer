#include "Material.h"
#include "Application.h"

Material::Material() :
	m_Shine(64.0f)
{
}

Material::~Material()
{
}

void Material::SetDiffuse(const std::string& texturePath, uint32_t slot)
{
	assert(texturePath.empty() == false);
	m_Diffuse = Texture(texturePath, slot);
}

void Material::Enable()
{
	m_Diffuse.Bind();
}

void Material::Disable()
{
	m_Diffuse.UnBind();
}
