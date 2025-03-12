#include "Material.h"
#include "Shader.h"
#include "Application.h"

Material::Material() :
	m_Shine(64.0f),
    m_AmbientColor(0.1f),
    m_SpecularColor(0.0f),
    m_DiffuseColor(1.0f)
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

void Material::SetSpecular(const std::string& texturePath, uint32_t slot)
{
    assert(texturePath.empty() == false);
    m_Specular = Texture(texturePath, slot);
}

void Material::OnRender(const std::shared_ptr<Shader>& shader)
{
    shader->SetUniformVector3("material.diffuseColor", m_DiffuseColor);
    shader->SetUniformVector3("material.specularColor", m_SpecularColor);
    shader->SetUniformVector3("material.ambientColor", m_AmbientColor);
    shader->SetUniformFloat("material.shine", m_Shine);

    if (m_Diffuse.IsLoaded())
    {
        shader->SetUniformInt("material.diffuse", m_Diffuse.GetSlot());
    }
    if (m_Specular.IsLoaded())
    {
        shader->SetUniformInt("material.specular", m_Specular.GetSlot());
    }
}

void Material::Enable()
{
    if (m_Diffuse.IsLoaded())
        m_Diffuse.Bind();
}

void Material::Disable()
{
    if (m_Diffuse.IsLoaded())
        m_Diffuse.UnBind();
}

Material Material::DefaultMaterial()
{
    return Material {};
}
