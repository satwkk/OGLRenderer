#pragma once

#include <memory>

#include "Shader.h"
#include "Mesh.h"
#include "Component.h"

class CVertexArray;
class CShader;

class CRenderer
{
public:
	bool Init();
	void ShutDown();

	void Render(CShader& shader, SMeshRendererComponent& meshRenderer, STransformComponent& transformComponent);	
	inline CRenderer* Get() { return s_pCInstance; }
private:
	CRenderer() = default;
	~CRenderer() = default;
	CRenderer(const CRenderer&) = delete;
	CRenderer(CRenderer&&) = delete;

public:
	static CRenderer* s_pCInstance;
};