#include "VertexArray.h"
#include "Buffer.h"

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
	glBindVertexArray(m_VAO);
}

void VertexArray::UnBind()
{
	glBindVertexArray(0);
}

void VertexArray::SetVertexBuffer(const SVertexBufferData& vertexData)
{
    Bind();
	m_VertexBufferData = vertexData;
    m_VertexBuffer = CreateBuffer(GL_ARRAY_BUFFER, m_VertexBufferData.Vertices);
}

void VertexArray::SetIndexBuffer(const std::vector<unsigned int>& indexData)
{
    Bind();
    m_IndexBuffer = CreateBuffer(GL_ELEMENT_ARRAY_BUFFER, indexData);
    m_IndexCount = indexData.size();
}

void VertexArray::PrepareVertexArray()
{
	Bind();

	for (uint32_t i = 0; i < m_VertexBufferData.BufferLayouts.size(); i++)
	{
		auto attribLayout = m_VertexBufferData.BufferLayouts[i];
		auto elementCount = GetCountFromAttribType(attribLayout.AttributeType);
		auto type = GetGLTypeFromAttribType(attribLayout.AttributeType);
		auto stride = m_VertexBufferData.GetStride();
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, elementCount, type, GL_FALSE, stride, (void*)attribLayout.Offset);
	}

	UnBind();
	/**
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);

	// Tex coord
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)12);

	// Normals
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)20);
	*/
}
