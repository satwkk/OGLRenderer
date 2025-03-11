#pragma once

#include <vector>
#include <filesystem>
#include <glm/glm.hpp>

#include "Mesh.h"
#include "Material.h"

class Shader;

class Model
{
public:
	Model() = default;
	~Model() = default;

	void AddMesh(const std::shared_ptr<Mesh>& mesh);
	inline std::vector<std::shared_ptr<Mesh>>& GetMeshArray() { return m_Meshes; }

public:
	glm::mat4 m_ModelMatrix;
	std::string Name{};
	std::filesystem::path AssetPath{};
	std::vector<std::shared_ptr<Mesh>> m_Meshes{};
};