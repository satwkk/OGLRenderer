#pragma once

#include "Framebuffer.h"
#include "Shader.h"
#include "Scene.h"

#include <glm/glm.hpp>

class CDirectionalLight
{
public:
    void Init(const glm::vec3& VInitialPosition, const glm::vec3& VInitialDirection);
    void Bind();
    void OnDraw(CShader& shader, CScene& scene);
    void Unbind();

    void SetPosition(const glm::vec3& pos);
    inline const glm::vec3& GetPosition() const { return m_VPosition; }
    inline const glm::mat4& GetViewProjectionMatrix() const { return m_MViewProjectionMatrix; }
    inline uint32_t GetShadowMap() { return m_CShadowMapFramebuffer.GetTexture(); }

private:
    glm::vec3 m_VPosition;
    glm::mat4 m_MViewProjectionMatrix;
    glm::mat4 m_MProjectionMatrix;
    CFramebuffer m_CShadowMapFramebuffer;
};
