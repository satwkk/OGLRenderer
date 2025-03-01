#pragma once

#include <memory>
#include <string>
#include <assimp/postprocess.h>

#include "Model.h"

#define BASICFLAGS aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace

class ModelLoader
{
private:
	ModelLoader() = default;
	~ModelLoader() = default;
	
public:
	static std::shared_ptr<Model> Load(const std::string& modelPath, unsigned int flags);

private:
};