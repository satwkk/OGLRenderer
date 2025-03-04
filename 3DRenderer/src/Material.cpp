#include "Material.h"
#include "Application.h"

Material::Material() :
	m_Shine(64.0f)
{
}

Material::~Material()
{
}

void Material::SetDiffuse(const std::string& texturePath)
{
	assert(texturePath.empty() == false);
	m_Diffuse = Texture(texturePath, 0);
}

void Material::SetAmbient(const std::string& texturePath)
{
	assert(texturePath.empty() == false);
	m_Ambient = Texture(texturePath, 2);
}

void Material::SetSpecular(const std::string& texturePath)
{
	assert(texturePath.empty() == false);
	m_Specular = Texture(texturePath, 1);
}

void Material::Enable()
{
	m_Shader = Application::Get()->GetShader();

	// Bind texture slots
	m_Shader->SetUniformInt("material.diffuse", 0);
	m_Shader->SetUniformInt("material.specular", 1);
	m_Shader->SetUniformFloat("material.shine", m_Shine);

	m_Diffuse.Bind();
	// m_Specular.Bind();
}

void Material::Disable()
{
	m_Diffuse.UnBind();
	// m_Specular.UnBind();
}
