#include <assert.h>
#include <memory>
#include <vector>

#include "assimp/material.h"
#include "ModelLoader.h"
#include "Utility.h"
#include "Logger.h"
#include "Material.h"

CModelLoader* CModelLoader::s_pCInstance = nullptr;

std::string CheckIfFileExistsInDir(const std::filesystem::path& CPath, const std::string& szFileName)
{
    if (std::filesystem::is_directory(CPath))
    {
        for (const std::filesystem::directory_entry& CEntry : std::filesystem::directory_iterator(CPath))
        {
            std::string szEntryName{ CUtility::GetFileNameFromPath(CEntry.path().string()) };
            if (szEntryName == szFileName)
            {
                return CEntry.path().string();
            }
        }
    }
    else
    {
        verr << "Provided path is not a directory\n";
    }
    return std::string{};
}

void SetMaterialTexture(aiMaterial* pMaterial, aiTextureType eTextureType, CMaterial& cMat, uint32_t uBindSlot, const std::string& szModelPath)
{
    aiString szPath{};
    if (pMaterial->GetTexture(eTextureType, 0, &szPath) == AI_SUCCESS)
    {
        // Get the local file path because for some reason assimp returns the remote path where asset was made.
        std::string szFileName{ CUtility::GetFileNameFromPath(std::string{ szPath.C_Str()})};
        std::filesystem::path szLocalPath{ szModelPath };
        std::string szTexturePath{ CheckIfFileExistsInDir(szLocalPath.parent_path(), szFileName)};

        if (szTexturePath.empty())
        {
            verr << "No texture file found in model directory...\n";
            return;
        }

        switch (eTextureType)
        {
            case aiTextureType_DIFFUSE:
            {
                cMat.SetDiffuse(szTexturePath, uBindSlot);
                break;
            }
            case aiTextureType_SPECULAR:
            {
                cMat.SetSpecular(szTexturePath, uBindSlot);
                break;
            }
            case aiTextureType_HEIGHT:
            {
                cMat.SetNormalMap(szTexturePath, uBindSlot);
                break;
            }
            default:
            {
                verr << "Unsupported texture path specified\n";
                break;
            }
        }
    }
}

std::shared_ptr<CModel> CModelLoader::Load(const std::string& modelPath, unsigned int flags)
{
    std::string szModelName{ CUtility::GetFileNameFromPath(modelPath) };
    auto& umLoadedModels = CModelLoader::GetInstance()->GetLoadedModels();
    auto itrModel = umLoadedModels.find(szModelName);
    if (itrModel != umLoadedModels.end())
    {
        vlog << "Found loaded model in cache, returning that ....\n";
        return std::make_shared<CModel>(itrModel->second);
    }

    auto importer = Assimp::Importer();
    const aiScene* pScene = importer.ReadFile(modelPath, flags);
    ASSERT(pScene != nullptr);

    std::shared_ptr<CModel> spModel = std::make_shared<CModel>();
    spModel->m_fsAssetPath = modelPath;
    spModel->m_sName = szModelName;

    for (uint32_t uMeshIndex = 0; uMeshIndex < pScene->mNumMeshes; uMeshIndex++)
    {
        auto* pMesh = pScene->mMeshes[uMeshIndex];
        std::shared_ptr<CMesh> spModelMesh = std::make_shared<CMesh>();
        SVertexBufferData sVertexData = {};
        std::vector<uint32_t> vIndexData = {};

        // Vertex buffer Setup
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

            aiVector3D& VTangent = pMesh->mTangents[i];
            sVertexData.vVertices.push_back(VTangent.x);
            sVertexData.vVertices.push_back(VTangent.y);
            sVertexData.vVertices.push_back(VTangent.z);
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
        sVertexData.vBufferLayouts.push_back({ EVertexAttributeType::Float3, 32 });

        spModelMesh->SetVertices(std::move(sVertexData));
        spModelMesh->SetIndices(std::move(vIndexData));

        // TEMP: Get normal map
        aiMaterial* pMeshMaterial = pScene->mMaterials[pMesh->mMaterialIndex];
        CMaterial cMyMaterial{};

        aiColor3D sDiffuseColor{};
        aiColor3D sSpecularColor{};
        aiColor3D sAmbientColor{};

        pMeshMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, sDiffuseColor);
        pMeshMaterial->Get(AI_MATKEY_COLOR_SPECULAR, sSpecularColor);
        pMeshMaterial->Get(AI_MATKEY_COLOR_AMBIENT, sAmbientColor);

        cMyMaterial.SetAmbientColor({ sDiffuseColor.r, sDiffuseColor.g, sDiffuseColor.b });
        cMyMaterial.SetDiffuseColor({ sDiffuseColor.r, sDiffuseColor.g, sDiffuseColor.b });
        cMyMaterial.SetSpecularColor({ sDiffuseColor.r, sDiffuseColor.g, sDiffuseColor.b });

        // TEMP: Remove later 
        cMyMaterial.SetDiffuse("./res/models/cottage/cottage_diffuse.png", uMeshIndex);
        cMyMaterial.SetNormalMap("./res/models/cottage/cottage_normal.png", uMeshIndex);

        /**
        SetMaterialTexture(pMeshMaterial, aiTextureType_DIFFUSE, cMyMaterial, uMeshIndex, modelPath);
        SetMaterialTexture(pMeshMaterial, aiTextureType_SPECULAR, cMyMaterial, uMeshIndex, modelPath);
        SetMaterialTexture(pMeshMaterial, aiTextureType_HEIGHT, cMyMaterial, uMeshIndex, modelPath);
         */

        spModelMesh->SetMaterial(std::move(cMyMaterial));
        spModelMesh->PrepareMesh();
        spModel->AddMesh(spModelMesh);
    }

    umLoadedModels.insert({ szModelName, *spModel });
    return spModel;
}
