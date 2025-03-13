#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "Logger.h"
#include "VertexArray.h"

Mesh::Mesh() :
    m_Material{}
{
    vlog << "mesh constructed\n";
    m_VertexArray = std::make_shared<VertexArray>();
}

Mesh::~Mesh()
{
    vlog << "mesh destructed\n";
}

void Mesh::SetVertices(const SVertexBufferData& vertexData)
{
    m_Vertices = vertexData.Vertices;
    m_VertexArray->SetVertexBuffer(vertexData);
}

void Mesh::SetIndices(const std::vector<uint32_t>& indexData)
{
    m_Indices = indexData;
    m_VertexArray->SetIndexBuffer(indexData);
}

void Mesh::PrepareMesh()
{
    m_VertexArray->PrepareVertexArray();
}

void Mesh::OnRender(Shader& shader)
{
    m_Material.OnRender(shader);
}

void Mesh::BeginRender()
{
	m_VertexArray->Bind();
	m_Material.Enable();
}

void Mesh::EndRender()
{
	m_Material.Disable();
	m_VertexArray->UnBind();
}
