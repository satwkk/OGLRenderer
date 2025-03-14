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

void CVertexArray::SetVertexBuffer(SVertexBufferData&& vertexData)
{
	Bind();
	m_SVertexBufferData = std::move(vertexData);
	m_uVertexBuffer = CreateBuffer(GL_ARRAY_BUFFER, m_SVertexBufferData.vVertices);
}

void CVertexArray::SetVertexBuffer(const SVertexBufferData& vertexData)
{
	Bind();
	m_SVertexBufferData = vertexData;
	m_uVertexBuffer = CreateBuffer(GL_ARRAY_BUFFER, m_SVertexBufferData.vVertices);
}

void CVertexArray::SetIndexBuffer(std::vector<unsigned int>&& indexData)
{
	Bind();
	m_vIndexBufferData = std::move(indexData);
	m_uIndexBuffer = CreateBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vIndexBufferData);
	m_uIndexCount = (uint32_t)m_vIndexBufferData.size();
}

void CVertexArray::SetIndexBuffer(const std::vector<unsigned int>& indexData)
{
	Bind();
	m_vIndexBufferData = indexData;
	m_uIndexBuffer = CreateBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vIndexBufferData);
	m_uIndexCount = (uint32_t)m_vIndexBufferData.size();
}

void CVertexArray::PrepareVertexArray()
{
	Bind();

	for (uint32_t i = 0; i < m_SVertexBufferData.vBufferLayouts.size(); i++)
	{
		auto vAttribLayout = m_SVertexBufferData.vBufferLayouts[i];
		auto uElementCount = GetCountFromAttribType(vAttribLayout.eAttributeType);
		auto eType = GetGLTypeFromAttribType(vAttribLayout.eAttributeType);
		auto uStride = m_SVertexBufferData.GetStride();
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, uElementCount, eType, GL_FALSE, uStride, (void*)vAttribLayout.nOffset);
	}

	UnBind();
}
