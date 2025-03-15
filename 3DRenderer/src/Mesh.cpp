#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "Logger.h"
#include "VertexArray.h"

CMesh::CMesh() :
    m_CMaterial{}
{
    vlog << "mesh constructed\n";
    m_spCVertexArray = std::make_shared<CVertexArray>();
}

CMesh::~CMesh()
{
    vlog << "mesh destructed\n";
}

void CMesh::SetVertices(SVertexBufferData&& vertexData)
{
    m_vVertices = vertexData.vVertices;
    m_spCVertexArray->SetVertexBuffer(std::move(vertexData));
}

void CMesh::SetVertices(const SVertexBufferData& vertexData)
{
    m_vVertices = vertexData.vVertices;
    m_spCVertexArray->SetVertexBuffer(vertexData);
}

void CMesh::SetIndices(std::vector<uint32_t>&& indexData)
{
    m_vIndices = indexData;
    m_spCVertexArray->SetIndexBuffer(std::move(indexData));
}

void CMesh::SetIndices(const std::vector<uint32_t>& indexData)
{
    m_vIndices = indexData;
    m_spCVertexArray->SetIndexBuffer(indexData);
}

void CMesh::PrepareMesh()
{
    m_spCVertexArray->PrepareVertexArray();
}

void CMesh::BeginRender()
{
	m_spCVertexArray->Bind();
	m_CMaterial.Enable();
}

void CMesh::OnRender(CShader& shader)
{
    m_CMaterial.OnRender(shader);
}

void CMesh::EndRender()
{
	m_CMaterial.Disable();
	m_spCVertexArray->UnBind();
}
