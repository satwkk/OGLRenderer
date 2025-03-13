#pragma once

#include <memory>

class CVertexArray;
class CShader;

class CRenderer
{
public:
	bool Init();
	void ShutDown();
	inline CRenderer* Get() { return s_pCInstance; }
	void Render(std::shared_ptr<CShader>& shader, std::shared_ptr<CVertexArray>& vertexArray);
	
private:
	CRenderer() = default;
	~CRenderer() = default;
	CRenderer(const CRenderer&) = delete;
	CRenderer(CRenderer&&) = delete;

public:
	static CRenderer* s_pCInstance;
};