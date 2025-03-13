#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "Logger.h"
#include "VertexArray.h"

CMesh::CMesh() :
    m_cMaterial{}
{
    vlog << "mesh constructed\n";
    m_spCVertexArray = std::make_shared<CVertexArray>();
}

CMesh::~CMesh()
{
    vlog << "mesh destructed\n";
}

void CMesh::SetVertices(const SVertexBufferData& vertexData)
{
    m_vVertices = vertexData.vVertices;
    m_spCVertexArray->SetVertexBuffer(vertexData);
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

void CMesh::OnRender(CShader& shader)
{
    m_cMaterial.OnRender(shader);
}

void CMesh::BeginRender()
{
	m_spCVertexArray->Bind();
	m_cMaterial.Enable();
}

void CMesh::EndRender()
{
	m_cMaterial.Disable();
	m_spCVertexArray->UnBind();
}
