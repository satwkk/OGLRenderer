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

	inline Material& GetMaterial() { return *m_Material; }

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
