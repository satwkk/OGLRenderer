#pragma once

#include <vector>
#include <filesystem>
#include <glm/glm.hpp>

#include "Mesh.h"

class CShader;

class CModel
{
public:
	CModel() = default;
	~CModel() = default;

	CModel(const CModel&);
	CModel& operator=(const CModel&);

	CModel(CModel&&);
	CModel& operator=(CModel&&);

	void AddMesh(const std::shared_ptr<CMesh>& pMesh);
	inline std::vector<std::shared_ptr<CMesh>>& GetMeshArray() { return m_vMeshes; }

public:
	glm::mat4 m_MModelMatrix;
	std::string m_sName{};
	std::filesystem::path m_fsAssetPath{};
	std::vector<std::shared_ptr<CMesh>> m_vMeshes{};
};
