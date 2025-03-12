#pragma once

#include <vector>
#include <memory>
#include <vector>

#include "Material.h"
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
    void OnRender(const std::shared_ptr<Shader>& shader);

    inline void SetMaterial(const Material& material) { m_Material = material; }
	inline const Material& GetMaterial() const { return m_Material; }

private:
    void SetVertices(const std::vector<float>& vertexData);
    void SetIndices(const std::vector<uint32_t>& indexData);
    void PrepareMesh();

public:
	Material m_Material;
	std::shared_ptr<VertexArray> m_VertexArray;

	friend class ModelLoader;
	friend class Model;
};
