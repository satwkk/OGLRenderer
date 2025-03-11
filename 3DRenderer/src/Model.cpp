#include "Model.h"
#include "Shader.h"
#include <GL/glew.h>

void Model::AddMesh(const std::shared_ptr<Mesh>& mesh)
{
	m_Meshes.push_back(mesh);
}
