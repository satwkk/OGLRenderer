#include "SceneRenderer.h"
#include "Component.h"
#include "Model.h"
#include "Shader.h"
#include "Mesh.h"

void CSceneRenderer::Draw(const std::shared_ptr<CMesh>& spMesh, glm::mat4& modelMatrix, const glm::vec3& position, CShader& shader)
{
    spMesh->BeginRender();

    // Setup model matrix
    modelMatrix = glm::mat4(1.0f) *
        translate(glm::mat4(1.0), position) *
        scale(glm::mat4(1.0), glm::vec3(0.3f));

    shader.SetUniformMatrix4("uModelMatrix", modelMatrix);

    // Setup material params
    spMesh->OnRender(shader);

    // Draw call
    glDrawElements(GL_TRIANGLES, spMesh->GetIndicesCount(), GL_UNSIGNED_INT, (void*)0);

    spMesh->EndRender();
}

void CSceneRenderer::Draw(const std::shared_ptr<CModel>& pCModel, const glm::vec3& position, CShader& shader)
{
    for (auto& spCMesh : pCModel->GetMeshArray())
    {
        Draw(spCMesh, pCModel->m_MModelMatrix, position, shader);
    }
}

void CSceneRenderer::Draw(CScene& scene, CShader& shader)
{
    auto& cRegistry = scene.GetSceneRegistry();
    auto cGroup = cRegistry.group<STransformComponent>(entt::get<SMeshRendererComponent>);

    for (auto uEntity : cGroup)
    {
        auto [sTransform, sMeshRenderer] = cGroup.get<STransformComponent, SMeshRendererComponent>(uEntity);  
        Draw(sMeshRenderer.m_spCModelRef, sTransform.VPosition, shader);
    }
}
