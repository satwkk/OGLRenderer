#include "VertexArray.h"

#include <assert.h>
#include <GL/glew.h>

VertexArray::VertexArray() :
	m_VAO(0)
{
	glCreateVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_VAO);
}

void VertexArray::Bind()
{
	assert(m_VertexBuffer != nullptr && m_IndexBuffer != nullptr);
	glBindVertexArray(m_VAO);
}

void VertexArray::UnBind()
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
	m_VertexBuffer = vertexBuffer;
	m_VertexBuffer->Bind();
}

void VertexArray::AddBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
	m_IndexBuffer = indexBuffer;
	m_IndexBuffer->Bind();
}

void VertexArray::SetupLayouts()
{
	Bind();

	// TODO: Abstract this when buffer layout is setup inside VertexBuffer class
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)12);

	UnBind();
}
