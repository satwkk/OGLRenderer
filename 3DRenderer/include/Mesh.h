#pragma once

#include <vector>
#include <memory>
#include <vector>

#include "Material.h"
#include "Shader.h"
#include "VertexArray.h"

class CShader;

class CMesh
{
public:
	CMesh();
	~CMesh();
	void BeginRender();
	void EndRender();

	inline CMaterial& GetMaterial() { return m_cMaterial; }
	inline std::shared_ptr<CVertexArray>& GetVertexArray() { return m_spCVertexArray; }
    void OnRender(CShader& shader);

    inline std::vector<float>& GetVertices() { return m_vVertices; }
    inline std::vector<uint32_t>& GetIndices() { return m_vIndices; }
    inline const uint32_t GetIndicesCount() const { return (uint32_t)m_vIndices.size(); }
    inline void SetMaterial(const CMaterial& material) { m_cMaterial = material; }
	inline const CMaterial& GetMaterial() const { return m_cMaterial; }

private:
    void SetVertices(const SVertexBufferData& vertexData);
    void SetIndices(const std::vector<uint32_t>& indexData);
    void PrepareMesh();

public:
	CMaterial m_cMaterial;
    std::vector<float> m_vVertices;
    std::vector<uint32_t> m_vIndices;
	std::shared_ptr<CVertexArray> m_spCVertexArray;

	friend class CModelLoader;
	friend class CModel;
};
