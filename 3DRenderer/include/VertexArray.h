#pragma once

#include "Buffer.h"
#include <memory>

class CVertexArray
{
public:
	CVertexArray();
	~CVertexArray();

	void Bind();
	void UnBind();

    void SetVertexBuffer(const SVertexBufferData& vertexData);
    void SetIndexBuffer(const std::vector<unsigned int>& indexData);
	void PrepareVertexArray();

	inline const uint32_t GetID() const { return m_uVAO; }
    inline const uint32_t GetIndexCount() const { return m_uIndexCount; }

private:
	uint32_t m_uVAO;
	SVertexBufferData m_SVertexBufferData;
    BufferID m_uVertexBuffer;
    BufferID m_uIndexBuffer;
    uint32_t m_uIndexCount;
};
