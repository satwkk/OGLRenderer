#include "Scene.h"
#include "ModelLoader.h"
#include "Component.h"
#include "Model.h"
#include "SceneRenderer.h"
#include "Mesh.h"

void Scene::InitScene()
{
    std::vector<std::shared_ptr<Model>> models = {
        ModelLoader::Load("./res/models/tree/Gledista_Triacanthos.fbx", BASICFLAGS),
        ModelLoader::Load("./res/models/tree/Gledista_Triacanthos_2.fbx", BASICFLAGS),
    };

    for (auto& model : models)
    {
	    entt::entity ent = m_Registry.create();
        srand(rand());
        float x = rand() % 5000;
        float z = rand() % 5000;
        m_Registry.emplace<TransformComponent>(ent, glm::vec3{ x, 0.0f, z }, glm::vec3{ 0.3f });
        m_Registry.emplace<MeshRendererComponent>(ent, model);
        m_SceneObjects.insert({ ent, model });
    }
}

// TODO(void): These rendering should be done by a scene renderer 
void Scene::OnUpdate(Shader& shader)
{
    SceneRenderer::Draw(*this, shader);
}

void Scene::CloseScene()
{
    for (auto& kv : m_SceneObjects)
    {
        auto& modelRef = kv.second;
        modelRef.reset();
    }
}
