#include "VertexArray.h"
#include "Buffer.h"

#include <assert.h>
#include <GL/glew.h>

CVertexArray::CVertexArray() :
	m_uVAO(0)
{
	glCreateVertexArrays(1, &m_uVAO);
	glBindVertexArray(m_uVAO);
}

CVertexArray::~CVertexArray()
{
	glDeleteVertexArrays(1, &m_uVAO);
}

void CVertexArray::Bind()
{
	glBindVertexArray(m_uVAO);
}

void CVertexArray::UnBind()
{
	glBindVertexArray(0);
}

void CVertexArray::SetVertexBuffer(const SVertexBufferData& vertexData)
{
    Bind();
	m_sVertexBufferData = vertexData;
    m_uVertexBuffer = CreateBuffer(GL_ARRAY_BUFFER, m_sVertexBufferData.vVertices);
}

void CVertexArray::SetIndexBuffer(const std::vector<unsigned int>& indexData)
{
    Bind();
    m_uIndexBuffer = CreateBuffer(GL_ELEMENT_ARRAY_BUFFER, indexData);
    m_uIndexCount = (uint32_t)indexData.size();
}

void CVertexArray::PrepareVertexArray()
{
	Bind();

	for (uint32_t i = 0; i < m_sVertexBufferData.vBufferLayouts.size(); i++)
	{
		auto attribLayout = m_sVertexBufferData.vBufferLayouts[i];
		auto elementCount = GetCountFromAttribType(attribLayout.eAttributeType);
		auto type = GetGLTypeFromAttribType(attribLayout.eAttributeType);
		auto stride = m_sVertexBufferData.GetStride();
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, elementCount, type, GL_FALSE, stride, (void*)attribLayout.nOffset);
	}

	UnBind();
}
