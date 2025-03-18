#include "Scene.h"
#include "ModelLoader.h"
#include "Component.h"
#include "Model.h"
#include "SceneRenderer.h"
#include "Mesh.h"

#include <GLFW/glfw3.h>
#include <memory>

void CScene::InitScene()
{
    std::vector<std::shared_ptr<CModel>> vHouseModels = {
        CModelLoader::Load("./res/models/cottage/cottage_fbx.fbx", BASICFLAGS),
        CModelLoader::Load("./res/models/cottage/cottage_fbx.fbx", BASICFLAGS),
        CModelLoader::Load("./res/models/cottage/cottage_fbx.fbx", BASICFLAGS),
        CModelLoader::Load("./res/models/cottage/cottage_fbx.fbx", BASICFLAGS),
        CModelLoader::Load("./res/models/cottage/cottage_fbx.fbx", BASICFLAGS),
        CModelLoader::Load("./res/models/cottage/cottage_fbx.fbx", BASICFLAGS)
    };
    
    float spacing = 2000.0f;
    for (uint32_t i = 0; i < vHouseModels.size(); i++)
    {
        std::shared_ptr<CModel> spCModel = vHouseModels[i];

	    entt::entity uEntityID = m_CRegistry.create();

        srand(rand());

        float n = (float)i / vHouseModels.size();
        float nn = n * 2.0f - 1.0f;
        glm::vec3 sPosition{ spacing * nn, 0.0f, 0.0f };
        glm::vec3 sRotation{ -90.0f, 0.0f, 0.0f };
        glm::vec3 sScale{ 200.0f, 200.0f, 100.0f };

        m_CRegistry.emplace<STransformComponent>(uEntityID, sPosition, sRotation, sScale);
        m_CRegistry.emplace<SMeshRendererComponent>(uEntityID, spCModel);
        m_umSceneObjectMap.insert({ uEntityID, spCModel });
    }
}

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
