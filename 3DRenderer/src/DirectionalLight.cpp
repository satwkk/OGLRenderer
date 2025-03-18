#include "DirectionalLight.h"
#include "Buffer.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

void CDirectionalLight::Init(const glm::vec3& VInitialPosition, const glm::vec3& VInitialDirection)
{
    FramebufferSpecification specs{};
    specs.uWidth = 1024;
    specs.uHeight = 1024;
    specs.bDisableColorBuffer = true;

    m_VPosition = VInitialPosition;
    m_CShadowMapFramebuffer = CFramebuffer(std::move(specs));
    glm::mat4 MLightProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
    glm::mat4 MLightView = glm::lookAt(m_VPosition, VInitialDirection, glm::vec3(0.0, 1.0, 0.0));
    m_MViewProjectionMatrix = MLightProjection * MLightView;
}

void CDirectionalLight::SetPosition(const glm::vec3& position)
{
    m_VPosition = position;
    glm::mat4 MLightProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
    glm::mat4 MLightView = glm::lookAt(m_VPosition, glm::vec3(0.0), glm::vec3(0.0, 1.0, 0.0));
    m_MViewProjectionMatrix = MLightProjection * MLightView;
}

void CDirectionalLight::Bind()
{
    m_CShadowMapFramebuffer.Bind();
}

void CDirectionalLight::Unbind()
{
    m_CShadowMapFramebuffer.Unbind();
}

void CDirectionalLight::OnDraw(CShader& shader, CScene& scene)
{
    // Set view port to shadow map width and height
    glViewport(0, 0, m_CShadowMapFramebuffer.GetWidth(), m_CShadowMapFramebuffer.GetHeight());

    // Bind shader
    shader.Bind();
    shader.SetUniformMatrix4("uVPMatrix", m_MViewProjectionMatrix);

    // Bind frame buffer
    Bind();

    // Clear the depth buffer
    glClear(GL_DEPTH_BUFFER_BIT);

    // Render to scene
    scene.OnUpdate(shader);

    // Unbind shader
    shader.UnBind();

    // Unbind frame buffer
    Unbind();
}
