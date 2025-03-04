#include "Model.h"

void Model::BeginRender()
{
	for (auto& mesh : m_Meshes)
	{
		mesh->BeginRender();
	}
}

void Model::EndRender()
{
	for (auto& mesh : m_Meshes)
	{
		mesh->EndRender();
	}
}

void Model::AddMesh(const std::shared_ptr<Mesh>& mesh)
{
	m_Meshes.push_back(mesh);
}
