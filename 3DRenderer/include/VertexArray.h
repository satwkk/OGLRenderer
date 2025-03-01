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

	void AddBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
	void AddBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
	void SetupLayouts();

	inline const unsigned int GetID() const { return m_VAO; }

private:
	unsigned int m_VAO;
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
};