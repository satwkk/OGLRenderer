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

	void OnDraw(std::shared_ptr<Shader>& shader);
	void SetPosition(const glm::vec3& newPosition);
	void AddMesh(const std::shared_ptr<Mesh>& mesh);

public:
	glm::vec3 m_Position = glm::vec3(0.0f);
	glm::mat4 m_ModelMatrix;
	std::string Name{};
	std::filesystem::path AssetPath{};
	std::vector<std::shared_ptr<Mesh>> m_Meshes{};
};