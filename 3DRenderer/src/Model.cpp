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
