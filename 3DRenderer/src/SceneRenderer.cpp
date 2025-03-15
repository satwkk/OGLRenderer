#include "SceneRenderer.h"
#include "Model.h"
#include "Shader.h"
#include "Mesh.h"

void CSceneRenderer::Draw(const std::shared_ptr<CMesh>& spMesh, glm::mat4& modelMatrix, STransformComponent& transform, CShader& shader)
{
    spMesh->BeginRender();

    glm::mat4 MRotationMatrix = 
        glm::rotate(glm::mat4(1.0), glm::radians(transform.VRotation.x), glm::vec3(1.0, 0.0, 0.0)) * 
        glm::rotate(glm::mat4(1.0), glm::radians(transform.VRotation.y), glm::vec3(0.0, 1.0, 0.0)) * 
        glm::rotate(glm::mat4(1.0), glm::radians(transform.VRotation.z), glm::vec3(0.0, 0.0, 1.0));

    // Setup model matrix
    modelMatrix = glm::mat4(1.0f) *
        translate(glm::mat4(1.0), transform.VPosition) *
        MRotationMatrix *
        scale(glm::mat4(1.0), transform.VScale);

    shader.SetUniformMatrix4("uModelMatrix", modelMatrix);

    // Setup material params
    spMesh->OnRender(shader);

    // Draw call
    glDrawElements(GL_TRIANGLES, spMesh->GetIndicesCount(), GL_UNSIGNED_INT, (void*)0);

    spMesh->EndRender();
}

void CSceneRenderer::Draw(const std::shared_ptr<CModel>& pCModel, STransformComponent& transform, CShader& shader)
{
    for (auto& spCMesh : pCModel->GetMeshArray())
    {
        Draw(spCMesh, pCModel->m_MModelMatrix, transform, shader);
    }
}

void CSceneRenderer::Draw(CScene& scene, CShader& shader)
{
    auto& cRegistry = scene.GetSceneRegistry();
    auto cGroup = cRegistry.group<STransformComponent>(entt::get<SMeshRendererComponent>);

    for (auto uEntity : cGroup)
    {
        auto [sTransform, sMeshRenderer] = cGroup.get<STransformComponent, SMeshRendererComponent>(uEntity);  
        Draw(sMeshRenderer.m_spCModelRef, sTransform, shader);
    }
}
