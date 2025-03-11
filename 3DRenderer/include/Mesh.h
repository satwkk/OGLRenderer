#pragma once

#include <vector>
#include <memory>
#include <vector>

#include "Material.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "Texture.h"

class Mesh
{
public:
	Mesh() = default;
	~Mesh() = default;
	void BeginRender();
	void EndRender();

	inline std::shared_ptr<Material>& GetMaterial() { return m_Material; }
	inline std::vector<float>& GetVertices() { return m_VertexData; }
	inline std::shared_ptr<VertexBuffer>& GetVertexRawBuffer() { return m_VertexBuffer; }
	inline std::shared_ptr<IndexBuffer>& GetIndexRawBuffer() { return m_IndexBuffer; }
	inline std::shared_ptr<VertexArray>& GetVertexArray() { return m_VertexArray; }
	inline std::vector<unsigned int>& GetIndices() { return m_IndexData; }

private:
	void RenderSetup();

public:
	std::shared_ptr<Material> m_Material;
	std::vector<float> m_VertexData;
	std::vector<unsigned int> m_IndexData;
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	std::shared_ptr<VertexArray> m_VertexArray;

	friend class ModelLoader;
	friend class Model;
};
