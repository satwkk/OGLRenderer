#pragma once

#include <memory>
#include <string>
#include <filesystem>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/material.h>

#include "Model.h"

#define BASICFLAGS aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_GenSmoothNormals

class ModelLoader
{
private:
	ModelLoader() = default;
	~ModelLoader() = default;
	
public:
	static std::shared_ptr<Model> Load(const std::string& modelPath, unsigned int flags);
	static std::string GetTextureFileNameFromMaterial(aiMaterial* material, aiTextureType type);
	static std::string GetTextureLocalPath(const std::filesystem::path& modelPath, const std::string& searchFileName);
};