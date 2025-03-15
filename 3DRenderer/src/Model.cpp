#include "Model.h"
#include "Shader.h"
#include <GL/glew.h>

CModel::CModel(const CModel& other)
{
	m_MModelMatrix = other.m_MModelMatrix;
	m_sName = other.m_sName;
	m_fsAssetPath = other.m_fsAssetPath;
	m_vMeshes = other.m_vMeshes;
}

CModel& CModel::operator=(const CModel& other)
{
	m_MModelMatrix = other.m_MModelMatrix;
	m_sName = other.m_sName;
	m_fsAssetPath = other.m_fsAssetPath;
	m_vMeshes = other.m_vMeshes;
	return *this;
}

CModel::CModel(CModel&& other)
{
	m_MModelMatrix = std::move(other.m_MModelMatrix);
	m_sName = std::move(other.m_sName);
	m_fsAssetPath = std::move(other.m_fsAssetPath);
	m_vMeshes = std::move(other.m_vMeshes);

	other.m_MModelMatrix = glm::mat4{ 0.0 };
	other.m_sName = std::string{};
	other.m_fsAssetPath = std::filesystem::path{};
	other.m_vMeshes.clear();
}

CModel& CModel::operator=(CModel&& other)
{
	m_MModelMatrix = std::move(other.m_MModelMatrix);
	m_sName = std::move(other.m_sName);
	m_fsAssetPath = std::move(other.m_fsAssetPath);
	m_vMeshes = std::move(other.m_vMeshes);

	other.m_MModelMatrix = glm::mat4{ 0.0 };
	other.m_sName = std::string{};
	other.m_fsAssetPath = std::filesystem::path{};
	other.m_vMeshes.clear();

	return *this;
}

void CModel::AddMesh(const std::shared_ptr<CMesh>& pMesh)
{
	m_vMeshes.push_back(pMesh);
}
