#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "Logger.h"

Mesh::Mesh() :
    m_Material{}
{
    vlog << "mesh constructed\n";
}

Mesh::~Mesh()
{
    vlog << "mesh destructed\n";
}

void Mesh::RenderSetup()
{
	m_VertexArray = std::make_shared<VertexArray>();
	m_VertexBuffer = std::make_shared<VertexBuffer>(m_VertexData);
	m_IndexBuffer = std::make_shared<IndexBuffer>(m_IndexData);

	m_VertexArray->AddBuffer(m_VertexBuffer);
	m_VertexArray->AddBuffer(m_IndexBuffer);
	m_VertexArray->SetupLayouts();
}

void Mesh::OnRender(const std::shared_ptr<Shader>& shader)
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
