#include "Model.h"
#include "Shader.h"
#include <GL/glew.h>

void CModel::AddMesh(const std::shared_ptr<CMesh>& pMesh)
{
	m_vMeshes.push_back(pMesh);
}
