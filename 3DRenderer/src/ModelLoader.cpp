#include <iostream>
#include <assert.h>
#include <vector>

#include "assimp/material.h"
#include "ufbx.h"
#include "ModelLoader.h"
#include "Utility.h"
#include "Logger.h"
#include "Material.h"

std::shared_ptr<Model> ModelLoader::Load(const std::string& modelPath, unsigned int flags)
{
    auto importer = Assimp::Importer();
    auto* scene = importer.ReadFile(modelPath, flags);
    assert(scene != nullptr);

    auto model = std::make_shared<Model>();
    model->AssetPath = modelPath;
    model->Name = Utility::GetFileNameFromPath(modelPath);

    for (uint32_t meshIdx = 0; meshIdx < scene->mNumMeshes; meshIdx++)
    {
        auto* mesh = scene->mMeshes[meshIdx];
        auto modelMesh = std::make_shared<Mesh>();
        std::vector<float> vertexData = {};
        std::vector<uint32_t> indexData = {};

        // Vertex Data Setup
        for (uint32_t i = 0; i < mesh->mNumVertices; i++)
        {
            auto vertex = mesh->mVertices[i];

            vertexData.push_back(vertex.x);
            vertexData.push_back(vertex.y);
            vertexData.push_back(vertex.z);

            auto texCoord = mesh->mTextureCoords[0][i];
            vertexData.push_back(texCoord.x);
            vertexData.push_back(texCoord.y);

            auto normal = mesh->mNormals[i];
            vertexData.push_back(normal.x);
            vertexData.push_back(normal.y);
            vertexData.push_back(normal.z);
        }

        // Index data setup
        for (uint32_t i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];
            for (uint32_t indicesIdx = 0; indicesIdx < face.mNumIndices; indicesIdx++)
            {
                indexData.push_back(face.mIndices[indicesIdx]);
            }
        }

        // Bind VAO VBO and IBO
        // TODO(void): Find a better way to do the following. Three calls for a simple setup is unnecessary and can be easily mistakened.
        // NOTE(void): I think creating the vao, vbo and ibo here directly will make the process much more clear instead of doing it inside RenderSetup
        modelMesh->SetVertices(vertexData);
        modelMesh->SetIndices(indexData);
        modelMesh->PrepareMesh();

        /**
        // Prepare materials
        uint32_t materialIndex = mesh->mMaterialIndex;
        aiMaterial* mat = scene->mMaterials[materialIndex];
        
        std::string diffuseFile = GetTextureFileNameFromMaterial(mat, aiTextureType_DIFFUSE);
        std::string diffuseFilePath = GetTextureLocalPath(model->AssetPath, diffuseFile);

        std::string specularFile = GetTextureFileNameFromMaterial(mat, aiTextureType_SPECULAR);
        std::string specularFilePath = GetTextureLocalPath(model->AssetPath, specularFile);

        // TODO: we will control which diffuse texture should be assigned when editor layer is implemented
        if (!diffuseFilePath.empty())
        {
            vlog << "Adding diffuse " << diffuseFilePath << " for mesh " << meshIdx << nl;
            modelMesh->m_Material.SetDiffuse(diffuseFilePath, meshIdx);
        }
        else 
        {
            vlog << "No diffuse texture for mesh " << meshIdx << " will be defaulting to diffuse color only" << nl;
        }

        if (!specularFilePath.empty())
        {
            vlog << "Adding specular " << specularFilePath << " for mesh " << meshIdx << nl;
            modelMesh->m_Material.SetSpecular(specularFilePath, meshIdx);
        }
        else 
        {
            vlog << "No specular texture for mesh " << meshIdx << " will be defaulting to diffuse color only" << nl;
        }
         */

        model->AddMesh(modelMesh);
    }

    return model;
}

std::string ModelLoader::GetTextureFileNameFromMaterial(aiMaterial* material, aiTextureType type)
{
    aiString path = {};
    if (material->GetTextureCount(type) <= 0)
    {
        return std::string{};
    }

    if (material->GetTexture(type, 0, &path) != AI_SUCCESS)
    {
        verr << "Could not load texture " << type << " from path: " << path.data << nl;
        return std::string{};
    }

    std::string pathStr{ path.C_Str()};
    return Utility::GetFileNameFromPath(pathStr);

}

std::string ModelLoader::GetTextureLocalPath(const std::filesystem::path& modelPath, const std::string& searchFileName)
{
    for (const auto entry : std::filesystem::directory_iterator(modelPath.parent_path()))
    {
        std::string entryStr = entry.path().string();
        std::string fileName = Utility::GetFileNameFromPath(entryStr);
        if (fileName == searchFileName)
        {
            return entryStr;
        }
    }

    return std::string{};
}
