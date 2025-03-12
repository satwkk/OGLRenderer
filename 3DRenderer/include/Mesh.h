#pragma once

#include <vector>
#include <memory>
#include <vector>

#include "Material.h"
#include "Shader.h"
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
	inline std::shared_ptr<VertexArray>& GetVertexArray() { return m_VertexArray; }
    void OnRender(Shader& shader);

    inline std::vector<float>& GetVertices() { return m_Vertices; }
    inline std::vector<uint32_t>& GetIndices() { return m_Indices; }
    inline const uint32_t GetIndicesCount() const { return (uint32_t)m_Indices.size(); }
    inline void SetMaterial(const Material& material) { m_Material = material; }
	inline const Material& GetMaterial() const { return m_Material; }

private:
    void SetVertices(const std::vector<float>& vertexData);
    void SetIndices(const std::vector<uint32_t>& indexData);
    void PrepareMesh();

public:
	Material m_Material;
    std::vector<float> m_Vertices;
    std::vector<uint32_t> m_Indices;
	std::shared_ptr<VertexArray> m_VertexArray;

	friend class ModelLoader;
	friend class Model;
};
