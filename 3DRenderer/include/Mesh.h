#pragma once

#include <vector>
#include <memory>
#include <vector>

#include "Material.h"
#include "Buffer.h"
#include "VertexArray.h"

class Shader;

class Mesh
{
public:
	Mesh();
	~Mesh();
	void BeginRender();
	void EndRender();

	inline Material& GetMaterial() { return m_Material; }
	inline std::vector<float>& GetVertices() { return m_VertexData; }
	inline std::shared_ptr<VertexBuffer>& GetVertexRawBuffer() { return m_VertexBuffer; }
	inline std::shared_ptr<IndexBuffer>& GetIndexRawBuffer() { return m_IndexBuffer; }
	inline std::shared_ptr<VertexArray>& GetVertexArray() { return m_VertexArray; }
	inline std::vector<unsigned int>& GetIndices() { return m_IndexData; }
    void OnRender(const std::shared_ptr<Shader>& shader);

    inline void SetMaterial(const Material& material) { m_Material = material; }
	inline const Material& GetMaterial() const { return m_Material; }
	inline const std::vector<float>& GetVertices() const { return m_VertexData; }
	inline const std::vector<unsigned int>& GetIndices() const { return m_IndexData; }

private:
	void RenderSetup();

public:
	Material m_Material;
	std::vector<float> m_VertexData;
	std::vector<unsigned int> m_IndexData;
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	std::shared_ptr<VertexArray> m_VertexArray;

	friend class ModelLoader;
	friend class Model;
};
