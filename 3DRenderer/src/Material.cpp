#include "Material.h"
#include "Shader.h"
#include "Application.h"

CMaterial::CMaterial() :
	m_fShine(64.0f),
    m_VAmbientColor(0.1f),
    m_VSpecularColor(0.0f),
    m_VDiffuseColor(1.0f)
{
}

CMaterial::~CMaterial()
{
}

void CMaterial::SetDiffuse(const std::string& texturePath, uint32_t slot)
{
	assert(texturePath.empty() == false);
	m_CDiffuse = CTexture(texturePath, slot);
}

void CMaterial::SetSpecular(const std::string& texturePath, uint32_t slot)
{
    assert(texturePath.empty() == false);
    m_CSpecular = CTexture(texturePath, slot);
}

void CMaterial::SetNormalMap(const std::string& texturePath, uint32_t slot)
{
    assert(texturePath.empty() == false);
    m_CNormalMap = CTexture(texturePath, slot);
}

void CMaterial::OnRender(CShader& shader)
{
    shader.SetUniformVector3("material.diffuseColor", m_VDiffuseColor);
    shader.SetUniformVector3("material.specularColor", m_VSpecularColor);
    shader.SetUniformVector3("material.ambientColor", m_VAmbientColor);
    shader.SetUniformFloat("material.shine", m_fShine);

    if (m_CDiffuse.IsLoaded())
    {
        shader.SetUniformInt("material.diffuse", m_CDiffuse.GetSlot());
    }
    if (m_CSpecular.IsLoaded())
    {
        shader.SetUniformInt("material.specular", m_CSpecular.GetSlot());
    }
    if (m_CNormalMap.IsLoaded())
    {
        shader.SetUniformInt("material.normalMap", m_CNormalMap.GetSlot());
    }
}

void CMaterial::Enable()
{
    if (m_CDiffuse.IsLoaded())
        m_CDiffuse.Bind();
}

void CMaterial::Disable()
{
    if (m_CDiffuse.IsLoaded())
        m_CDiffuse.UnBind();
}

CMaterial CMaterial::DefaultMaterial()
{
    return CMaterial {};
}
