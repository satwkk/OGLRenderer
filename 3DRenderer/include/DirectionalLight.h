#pragma once

#include "Framebuffer.h"
#include "Shader.h"
#include "Scene.h"

#include <glm/glm.hpp>

class CDirectionalLight
{
public:
    void Init(const glm::vec3& VInitialPosition, const glm::vec3& VDirection);
    void Bind();
    void OnDraw(CShader& shader, CScene& scene);
    void Unbind();

    void SetRotation(const glm::vec3& rotation);
    inline const glm::vec3& GetPosition() const { return m_VPosition; }
    inline const glm::vec3& GetDirection() const { return m_VDirection; }
    inline const glm::mat4& GetViewProjectionMatrix() const { return m_MViewProjectionMatrix; }
    inline uint32_t GetShadowMap() { return m_CShadowMapFramebuffer.GetTexture(); }

private:
    glm::vec3 m_VPosition;
    glm::mat3 m_MRotation;
    glm::vec3 m_VDirection;
    glm::mat4 m_MViewProjectionMatrix;
    glm::mat4 m_MProjectionMatrix;
    CFramebuffer m_CShadowMapFramebuffer;
};
