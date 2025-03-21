#include <filesystem>

#include "ShaderLibrary.h"
#include "Utility.h"

CShaderLibrary* CShaderLibrary::s_pCInstance = nullptr;

void CShaderLibrary::Init()
{
    m_LibraryMap.emplace("cubemap", CShader("./shaders/cubemap/vertex.glsl", "./shaders/cubemap/fragment.glsl"));
    m_LibraryMap.emplace("phong", CShader("./shaders/phong/vertex.glsl", "./shaders/phong/fragment.glsl"));
    m_LibraryMap.emplace("shadowmap", CShader("./shaders/phong/ShadowMapVertexShader.glsl", "./shaders/phong/ShadowMapFragmentShader.glsl"));
}

CShaderLibrary* CShaderLibrary::Get()
{
	if (s_pCInstance == nullptr)
	{
		s_pCInstance = new CShaderLibrary;
	}
	return s_pCInstance;
}

CShader& CShaderLibrary::GetShader(const ShaderID& id)
{
	const auto it = m_LibraryMap.find(id);
	ASSERT(it != m_LibraryMap.end());
	return it->second;
}
