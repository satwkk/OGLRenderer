#include "Scene.h"
#include "SceneObject.h"
#include "ModelLoader.h"
#include "Component.h"
#include "Model.h"
#include "Shader.h"
#include "Mesh.h"

void Scene::InitDebugScene()
{
    m_DebugModels = {
        ModelLoader::Load("./res/models/tree/Gledista_Triacanthos.fbx", BASICFLAGS),
        ModelLoader::Load("./res/models/tree/Gledista_Triacanthos_2.fbx", BASICFLAGS)
    };

    for (auto& model : m_DebugModels)
    {
	    entt::entity ent = m_Registry.create();
        float x = rand() % 200;
        float z = rand() % 200;
        m_Registry.emplace<TransformComponent>(ent, glm::vec3(x, 0.0f, z));
        m_Registry.emplace<MeshRendererComponent>(ent, model);
        m_SceneObjects.insert({ ent, model });
    }
}

void Scene::OnUpdate(std::shared_ptr<Shader>& shader)
{
    auto group = m_Registry.group<TransformComponent>(entt::get<MeshRendererComponent>);
    
    for (auto entity : group)
    {
        auto [transform, meshRenderer] = group.get<TransformComponent, MeshRendererComponent>(entity);

        for (auto& mesh : meshRenderer.ModelRef->GetMeshArray())
        {
            mesh->BeginRender();

            // Setup model matrix
            meshRenderer.ModelRef->m_ModelMatrix = glm::mat4(1.0f) * 
                glm::translate(glm::mat4(1.0), transform.Position) *
                glm::scale(glm::mat4(1.0), glm::vec3(0.3f));

            shader->SetUniformMatrix4("uModelMatrix", meshRenderer.ModelRef->m_ModelMatrix);

            // Setup material params
            shader->SetUniformInt("material.diffuse", mesh->GetMaterial()->GetDiffuseMapSlotIndex());
            shader->SetUniformFloat("material.shine", mesh->GetMaterial()->GetShine());

            // Draw call
            glDrawElements(GL_TRIANGLES, mesh->m_IndexData.size(), GL_UNSIGNED_INT, (void*)0);

            mesh->EndRender();
        }
    }
}