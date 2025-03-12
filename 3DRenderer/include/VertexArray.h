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

    void SetVertexBuffer(const std::vector<float>& vertexData);
    void SetIndexBuffer(const std::vector<unsigned int>& indexData);
	void SetupLayouts();

	inline const uint32_t GetID() const { return m_VAO; }
    inline const uint32_t GetIndexCount() const { return m_IndexCount; }

private:
	uint32_t m_VAO;
    BufferID m_VertexBuffer;
    BufferID m_IndexBuffer;
    uint32_t m_IndexCount;
};
