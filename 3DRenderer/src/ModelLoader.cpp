#include <iostream>
#include <assert.h>
#include <vector>

#include "assimp/material.h"
#include "ufbx.h"
#include "ModelLoader.h"
#include "Utility.h"
#include "Logger.h"
#include "Material.h"

std::shared_ptr<CModel> CModelLoader::Load(const std::string& modelPath, unsigned int flags)
{
    auto importer = Assimp::Importer();
    const aiScene* pScene = importer.ReadFile(modelPath, flags);
    assert(pScene != nullptr);

    std::shared_ptr<CModel> spModel = std::make_shared<CModel>();
    spModel->m_fsAssetPath = modelPath;
    spModel->m_sName = CUtility::GetFileNameFromPath(modelPath);

    for (uint32_t meshIdx = 0; meshIdx < pScene->mNumMeshes; meshIdx++)
    {
        auto* pMesh = pScene->mMeshes[meshIdx];
        std::shared_ptr<CMesh> spModelMesh = std::make_shared<CMesh>();
        SVertexBufferData sVertexData = {};
        std::vector<uint32_t> vIndexData = {};

        // Vertex Data Setup
        for (uint32_t i = 0; i < pMesh->mNumVertices; i++)
        {
            aiVector3D& VVertex = pMesh->mVertices[i];

            sVertexData.vVertices.push_back(VVertex.x);
            sVertexData.vVertices.push_back(VVertex.y);
            sVertexData.vVertices.push_back(VVertex.z);

            aiVector3D& VTexCoord = pMesh->mTextureCoords[0][i];
            sVertexData.vVertices.push_back(VTexCoord.x);
            sVertexData.vVertices.push_back(VTexCoord.y);

            aiVector3D& VNormal = pMesh->mNormals[i];
            sVertexData.vVertices.push_back(VNormal.x);
            sVertexData.vVertices.push_back(VNormal.y);
            sVertexData.vVertices.push_back(VNormal.z);
        }

        // Index data setup
        for (uint32_t i = 0; i < pMesh->mNumFaces; i++)
        {
            auto sFace = pMesh->mFaces[i];
            for (uint32_t indicesIdx = 0; indicesIdx < sFace.mNumIndices; indicesIdx++)
            {
                vIndexData.push_back(sFace.mIndices[indicesIdx]);
            }
        }

        sVertexData.vBufferLayouts.push_back({ EVertexAttributeType::Float3, 0 });
        sVertexData.vBufferLayouts.push_back({ EVertexAttributeType::Float2, 12 });
        sVertexData.vBufferLayouts.push_back({ EVertexAttributeType::Float3, 20 });

        spModelMesh->SetVertices(std::move(sVertexData));
        spModelMesh->SetIndices(std::move(vIndexData));
        spModelMesh->PrepareMesh();
        spModel->AddMesh(spModelMesh);
    }

    return spModel;
}

std::string CModelLoader::GetTextureFileNameFromMaterial(aiMaterial* pMaterial, aiTextureType type)
{
    aiString sPath = {};
    if (pMaterial->GetTextureCount(type) <= 0)
    {
        return std::string{};
    }

    if (pMaterial->GetTexture(type, 0, &sPath) != AI_SUCCESS)
    {
        verr << "Could not load texture " << type << " from path: " << sPath.data << nl;
        return std::string{};
    }

    std::string sPathStr{ sPath.C_Str()};
    return CUtility::GetFileNameFromPath(sPathStr);

}

std::string CModelLoader::GetTextureLocalPath(const std::filesystem::path& modelPath, const std::string& searchFileName)
{
    for (const auto entry : std::filesystem::directory_iterator(modelPath.parent_path()))
    {
        std::string entryStr = entry.path().string();
        std::string fileName = CUtility::GetFileNameFromPath(entryStr);
        if (fileName == searchFileName)
        {
            return entryStr;
        }
    }

    return std::string{};
}
