#include "Material.h"
#include "Shader.h"
#include "Application.h"
#include "Window.h"

CMaterial::CMaterial() :
	m_fShine(64.0f),
    m_VAmbientColor(0.1f),
    m_VSpecularColor(0.0f),
    m_VDiffuseColor(1.0f),
    m_uAvailableSlot(0)
{
}

CMaterial::~CMaterial()
{
}

void CMaterial::SetDiffuse(const std::string& texturePath, uint32_t slot)
{
	assert(texturePath.empty() == false);
	m_CDiffuse = CTexture(texturePath, m_uAvailableSlot++);
}

void CMaterial::SetSpecular(const std::string& texturePath, uint32_t slot)
{
    assert(texturePath.empty() == false);
    m_CSpecular = CTexture(texturePath, m_uAvailableSlot++);
}

void CMaterial::SetNormalMap(const std::string& texturePath, uint32_t slot)
{
    assert(texturePath.empty() == false);
    m_CNormalMap = CTexture(texturePath, m_uAvailableSlot++);
}

void CMaterial::EnableShadowMap(CShader& shader)
{
    shader.SetUniformInt("uShadowMap", m_uAvailableSlot++);
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

    // TEMP: Very temporary !!!
    uint32_t tex = CApplication::Get()->GetDirectionalLight().GetShadowMap();
    glActiveTexture(GL_TEXTURE0 + m_uAvailableSlot);
    glBindTexture(GL_TEXTURE_2D, tex);
    shader.SetUniformInt("uShadowMap", m_uAvailableSlot);
}

void CMaterial::Enable()
{
    if (m_CDiffuse.IsLoaded())
        m_CDiffuse.Bind();

    if (m_CSpecular.IsLoaded())
        m_CSpecular.Bind();

    if (m_CNormalMap.IsLoaded())
        m_CNormalMap.Bind();
}

void CMaterial::Disable()
{
    if (m_CDiffuse.IsLoaded())
        m_CDiffuse.UnBind();

    if (m_CSpecular.IsLoaded())
        m_CSpecular.UnBind();

    if (m_CNormalMap.IsLoaded())
        m_CNormalMap.UnBind();
}

CMaterial CMaterial::DefaultMaterial()
{
    return CMaterial {};
}
