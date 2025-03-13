#pragma once

#include "Buffer.h"
#include <memory>

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind();
	void UnBind();

    void SetVertexBuffer(const SVertexBufferData& vertexData);
    void SetIndexBuffer(const std::vector<unsigned int>& indexData);
	void PrepareVertexArray();

	inline const uint32_t GetID() const { return m_VAO; }
    inline const uint32_t GetIndexCount() const { return m_IndexCount; }

private:
	uint32_t m_VAO;
	SVertexBufferData m_VertexBufferData;
    BufferID m_VertexBuffer;
    BufferID m_IndexBuffer;
    uint32_t m_IndexCount;
};
