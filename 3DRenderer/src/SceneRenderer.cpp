#include "SceneRenderer.h"
#include "Component.h"
#include "Model.h"
#include "Shader.h"
#include "Mesh.h"

void SceneRenderer::Draw(const std::shared_ptr<Mesh>& mesh, glm::mat4& modelMatrix, const glm::vec3& position, const std::shared_ptr<Shader>& shader)
{
    mesh->BeginRender();

    // Setup model matrix
    modelMatrix = glm::mat4(1.0f) *
        glm::translate(glm::mat4(1.0), position) *
        glm::scale(glm::mat4(1.0), glm::vec3(0.3f));

    shader->SetUniformMatrix4("uModelMatrix", modelMatrix);

    // Setup material params
    mesh->OnRender(shader);

    // Draw call
    glDrawElements(GL_TRIANGLES, mesh->GetIndices().size(), GL_UNSIGNED_INT, (void*)0);

    mesh->EndRender();
}

void SceneRenderer::Draw(const std::shared_ptr<Model>& model, const glm::vec3& position, const std::shared_ptr<Shader>& shader)
{
    for (auto& mesh : model->GetMeshArray())
    {
        Draw(mesh, model->m_ModelMatrix, position, shader);
    }
}

void SceneRenderer::Draw(Scene& scene, const std::shared_ptr<Shader>& shader)
{
    auto& registry = scene.GetSceneRegistry();
    auto group = registry.group<TransformComponent>(entt::get<MeshRendererComponent>);

    for (auto entity : group)
    {
        auto [transform, meshRenderer] = group.get<TransformComponent, MeshRendererComponent>(entity);
        Draw(meshRenderer.ModelRef, transform.Position, shader);
    }
}
