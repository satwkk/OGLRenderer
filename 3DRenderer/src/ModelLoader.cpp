#include "ModelLoader.h"
#include "Utility.h"
#include <iostream>
#include <assert.h>
#include <vector>
#include <filesystem>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>

std::shared_ptr<Model> ModelLoader::Load(const std::string& modelPath, unsigned int flags)
{
    auto importer = Assimp::Importer();
    auto* scene = importer.ReadFile(modelPath, flags);
    assert(scene != nullptr);

    std::shared_ptr<Model> model = std::make_shared<Model>();
    model->AssetPath = modelPath;
    model->Name = Utility::GetFileNameFromPath(modelPath);
    std::cout << "Model " << model->Name << " loaded." << std::endl;

    for (uint32_t meshIdx = 0; meshIdx < scene->mNumMeshes; meshIdx++)
    {
        auto* mesh = scene->mMeshes[meshIdx];
        std::shared_ptr<Mesh> modelMesh = std::make_shared<Mesh>();

        for (uint32_t i = 0; i < mesh->mNumVertices; i++)
        {
            auto vertex = mesh->mVertices[i];

            modelMesh->m_VertexData.push_back(vertex.x);
            modelMesh->m_VertexData.push_back(vertex.y);
            modelMesh->m_VertexData.push_back(vertex.z);

            auto texCoord = mesh->mTextureCoords[0][i];
            modelMesh->m_VertexData.push_back(texCoord.x);
            modelMesh->m_VertexData.push_back(texCoord.y);

            auto normal = mesh->mNormals[i];
            modelMesh->m_VertexData.push_back(normal.x);
            modelMesh->m_VertexData.push_back(normal.y);
            modelMesh->m_VertexData.push_back(normal.z);
        }

        for (uint32_t i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];
            for (uint32_t indicesIdx = 0; indicesIdx < face.mNumIndices; indicesIdx++)
            {
                modelMesh->m_IndexData.push_back(face.mIndices[indicesIdx]);
            }
        }

        modelMesh->RenderSetup();
        model->m_Meshes.push_back(modelMesh);
    }

    // Load the materials
    LoadMaterial(model);

    return model;
}

void ModelLoader::LoadMaterial(std::shared_ptr<Model>& model)
{
    // TODO: Each mesh will have separate textures for their materials
    for (auto& mesh : model->m_Meshes)
    {
        mesh->m_Material->SetDiffuse("./res/textures/ContainerDiffuse.png");
        mesh->m_Material->SetSpecular("./res/textures/ContainerSpecular.png");
    }
}
