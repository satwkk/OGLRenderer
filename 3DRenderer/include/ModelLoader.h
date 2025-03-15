#pragma once

#include <memory>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/material.h>

#include "Model.h"

#define BASICFLAGS aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_GenSmoothNormals

class CModelLoader
{
private:
	CModelLoader() = default;
	~CModelLoader() = default;
	
public:
	static std::shared_ptr<CModel> Load(const std::string& modelPath, unsigned int flags);
	static std::string GetTextureFileNameFromMaterial(aiMaterial* pMaterial, aiTextureType type);
	static std::string GetTextureLocalPath(const std::filesystem::path& modelPath, const std::string& searchFileName);
	static CModelLoader* GetInstance()
	{
		if (s_pCInstance == nullptr)
		{
			s_pCInstance = new CModelLoader;
		}
		return s_pCInstance;
	}

	inline std::unordered_map<std::string, CModel>& GetLoadedModels() { return m_umModelMap; }

private:
	static CModelLoader* s_pCInstance;
	std::unordered_map<std::string, CModel> m_umModelMap;
};