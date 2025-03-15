#include "Scene.h"
#include "ModelLoader.h"
#include "Component.h"
#include "Model.h"
#include "SceneRenderer.h"
#include "Mesh.h"

void CScene::InitScene()
{
    std::vector<std::shared_ptr<CModel>> vModels = {
        CModelLoader::Load("./res/models/cottage/cottage_fbx.fbx", BASICFLAGS),
        CModelLoader::Load("./res/models/cottage/cottage_fbx.fbx", BASICFLAGS),
        CModelLoader::Load("./res/models/cottage/cottage_fbx.fbx", BASICFLAGS),
        CModelLoader::Load("./res/models/cottage/cottage_fbx.fbx", BASICFLAGS),
    };

    for (auto& spCModel : vModels)
    {
	    entt::entity uEntityID = m_CRegistry.create();

        srand(rand());
        bool posMultiply1 = rand() % 10 > 5;
        bool posMultiply2 = rand() % 10 > 5;
        float fXPos = 1000 + rand() % 1000;
        float fZPos = 1000 + rand() % 1000;
        fXPos *= posMultiply1 ? 1 : -1;
        fZPos *= posMultiply2 ? 1 : -1;

        glm::vec3 sPosition { fXPos, 0.0f, fZPos };
        glm::vec3 sRotation{ 90.0f, 0.0f, 0.0f };
        glm::vec3 sScale { 500.0f, 500.0f, 200.0f };

        m_CRegistry.emplace<STransformComponent>(uEntityID, sPosition, sRotation, sScale);
        m_CRegistry.emplace<SMeshRendererComponent>(uEntityID, spCModel);
        m_umSceneObjectMap.insert({ uEntityID, spCModel });
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
        std::shared_ptr<CModel> spCModelRef = paSceneObject.second;
        spCModelRef.reset();
    }
}
