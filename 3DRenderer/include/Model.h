#pragma once

#include <vector>
#include <filesystem>
#include "Mesh.h"
#include "Material.h"

class Model
{
public:
	Model() = default;
	~Model() = default;
	void BeginRender();
	void EndRender();

public:
	std::string Name{};
	std::filesystem::path AssetPath{};
	std::vector<std::shared_ptr<Mesh>> m_Meshes{};
};