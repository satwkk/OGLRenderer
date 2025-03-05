#include "Model.h"
#include "Shader.h"
#include <GL/glew.h>

void Model::OnDraw(std::shared_ptr<Shader>& shader)
{
	for (auto& mesh : m_Meshes)
	{
		mesh->BeginRender();

		// Setup model matrix
		m_ModelMatrix = glm::mat4(1.0f);
		m_ModelMatrix = glm::translate(m_ModelMatrix, m_Position);
		m_ModelMatrix = glm::scale(m_ModelMatrix, glm::vec3(0.2f));
		shader->SetUniformMatrix4("uModelMatrix", m_ModelMatrix);

		// Setup material params
		shader->SetUniformInt("material.diffuse", mesh->GetMaterial().GetDiffuseMapSlotIndex());
		shader->SetUniformFloat("material.shine", mesh->GetMaterial().GetShine());

		// Draw call
		glDrawElements(GL_TRIANGLES, mesh->m_IndexData.size(), GL_UNSIGNED_INT, (void*)0);

		mesh->EndRender();
	}
}

void Model::SetPosition(const glm::vec3& newPosition)
{
	m_Position = newPosition;
}

void Model::AddMesh(const std::shared_ptr<Mesh>& mesh)
{
	m_Meshes.push_back(mesh);
}
