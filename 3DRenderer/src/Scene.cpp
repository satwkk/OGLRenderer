#include "Scene.h"
#include "ModelLoader.h"
#include "Component.h"
#include "Model.h"
#include "SceneRenderer.h"
#include "Mesh.h"

void CScene::InitScene()
{
    std::vector<std::shared_ptr<CModel>> vModels = {
        CModelLoader::Load("./res/models/tree/Gledista_Triacanthos.fbx", BASICFLAGS),
        CModelLoader::Load("./res/models/tree/Gledista_Triacanthos_2.fbx", BASICFLAGS),
    };

    for (auto& pCModel : vModels)
    {
	    entt::entity uEntityID = m_cRegistry.create();
        srand(rand());
        float fXPos = rand() % 5000;
        float fZPos = rand() % 5000;
        m_cRegistry.emplace<STransformComponent>(uEntityID, glm::vec3{ fXPos, 0.0f, fZPos }, glm::vec3{ 0.3f });
        m_cRegistry.emplace<SMeshRendererComponent>(uEntityID, pCModel);
        m_umSceneObjectMap.insert({ uEntityID, pCModel });
    }
}

// TODO(void): These rendering should be done by a scene renderer 
void CScene::OnUpdate(CShader& shader)
{
    CSceneRenderer::Draw(*this, shader);
}

void CScene::CloseScene()
{
    for (auto& paSceneObject : m_umSceneObjectMap)
    {
        std::shared_ptr<CModel> spModelRef = paSceneObject.second;
        spModelRef.reset();
    }
}
