#include "DirectionalLight.h"
#include "Buffer.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"

void CDirectionalLight::Init(const glm::vec3& VInitialPosition, const glm::vec3& VDirection)
{
    FramebufferSpecification specs{};
    specs.uWidth = 1024;
    specs.uHeight = 1024;
    specs.bDisableColorBuffer = true;

    m_VPosition = VInitialPosition;

    m_CShadowMapFramebuffer = CFramebuffer(std::move(specs));

    m_MProjectionMatrix = glm::ortho(-1000.0f, 1000.0f, 0.0f, 1000.0f, 1.f, 2000.0f);

    glm::mat4 MLightView = glm::lookAt(m_VPosition, m_VPosition + VDirection, glm::vec3(0.0, 1.0, 0.0));

    m_MViewProjectionMatrix = m_MProjectionMatrix * MLightView;

    m_MRotation = glm::mat3(MLightView);
    m_VDirection = VDirection;
}

void CDirectionalLight::SetRotation(const glm::vec3& rotation)
{
    glm::mat4 MNewRotation = glm::mat4(m_MRotation);
    MNewRotation = glm::rotate(glm::mat4(MNewRotation), glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
    MNewRotation = glm::rotate(glm::mat4(MNewRotation), glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0)); 
    MNewRotation = glm::rotate(glm::mat4(MNewRotation), glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));

    glm::vec3 VForwardVector = glm::mat3(MNewRotation) * glm::vec3(0.0, 0.0, -1.0);
    glm::vec3 VRightVector = glm::normalize(glm::cross(glm::vec3(0.0, 1.0, 0.0), VForwardVector));
    glm::vec3 VUpVector = glm::normalize(glm::cross(VForwardVector, VRightVector));
    
    glm::mat4 MNewViewMatrix = glm::lookAt(m_VPosition, m_VPosition + VForwardVector, VUpVector);

    m_MViewProjectionMatrix = m_MProjectionMatrix * MNewViewMatrix;

    m_MRotation = glm::mat3(MNewViewMatrix);
    m_VDirection = VForwardVector;
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

    glClear(GL_DEPTH_BUFFER_BIT);

    // Render to scene
    scene.OnUpdate(shader);

    // Unbind shader
    shader.UnBind();

    // Unbind frame buffer
    Unbind();
}
