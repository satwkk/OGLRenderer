#pragma once

#include <vector>

class VertexBuffer
{
public:
	VertexBuffer(const std::vector<float>& vertices);
	VertexBuffer(float* vertices, uint32_t count);
	~VertexBuffer();

	void Bind();
	void UnBind();
private:
	unsigned int m_RendererID;
};

class IndexBuffer
{
public:
	IndexBuffer(const std::vector<unsigned int>& vertices);
	IndexBuffer(float* indices, uint32_t count);
	~IndexBuffer();

	void Bind();
	void UnBind();
private:
	unsigned int m_RendererID;
};
