#include "ModelLoader.h"
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>

std::shared_ptr<Model> ModelLoader::Load(const std::string& modelPath, unsigned int flags)
{
    auto importer = Assimp::Importer();
    auto* scene = importer.ReadFile(modelPath, flags);
    std::shared_ptr<Model> model = std::make_shared<Model>();

    for (uint32_t meshIdx = 0; meshIdx < scene->mNumMeshes; meshIdx++)
    {
        auto* mesh = scene->mMeshes[meshIdx];

        for (uint32_t i = 0; i < mesh->mNumVertices; i++)
        {
            auto vertex = mesh->mVertices[i];
            model->VertexData.push_back(vertex.x);
            model->VertexData.push_back(vertex.y);
            model->VertexData.push_back(vertex.z);

            auto texCoord = mesh->mTextureCoords[0][i];
            model->VertexData.push_back(texCoord.x);
            model->VertexData.push_back(texCoord.y);
        }

        for (uint32_t i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];
            for (uint32_t indicesIdx = 0; indicesIdx < face.mNumIndices; indicesIdx++)
            {
                model->IndexData.push_back(face.mIndices[indicesIdx]);
            }
        }
    }
    return model;
}
