#include <iostream>
#include <assert.h>
#include <vector>

#include "ufbx.h"
#include "ModelLoader.h"
#include "Utility.h"
#include "Logger.h"

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

        // Vertex Data Setup
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

        // Index data setup
        for (uint32_t i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];
            for (uint32_t indicesIdx = 0; indicesIdx < face.mNumIndices; indicesIdx++)
            {
                modelMesh->m_IndexData.push_back(face.mIndices[indicesIdx]);
            }
        }

        // Bind VAO VBO and IBO
        // TODO(void): Find a better way to do the following. Two calls for a simple setup is unnecessary and can be easily mistakened.
        // NOTE(void): I think creating the vao, vbo and ibo here directly will make the process much more clear instead of doing it inside RenderSetup
        modelMesh->RenderSetup();

        // Prepare materials
        uint32_t materialIndex = mesh->mMaterialIndex;
        auto* mat = scene->mMaterials[materialIndex];
        
        std::string diffuseFile = GetTextureFileNameFromMaterial(mat, aiTextureType_DIFFUSE);
        std::string specularFile = GetTextureFileNameFromMaterial(mat, aiTextureType_SPECULAR);

        std::string diffuseFilePath = GetTextureLocalPath(model->AssetPath, diffuseFile);
        // std::string specularFilePath = GetTextureLocalPath(model->AssetPath, specularFile);

        // TODO: Create a function inside mesh called AddMaterial
        vlog << "Adding diffuse " << diffuseFilePath << nl;
        modelMesh->m_Material->SetDiffuse("./res/models/tree/gleditsia triacanthos bark2 a1.jpg");
        //modelMesh->m_Material->SetDiffuse(diffuseFilePath);
        // modelMesh->m_Material->SetSpecular(specularFilePath);

        model->AddMesh(modelMesh);
    }

    return model;
}

std::string ModelLoader::GetTextureFileNameFromMaterial(aiMaterial* material, aiTextureType type)
{
    aiString path = {};
    if (material->GetTextureCount(type) <= 0)
    {
        vwarn << "texture " << type << " not found\n";
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
