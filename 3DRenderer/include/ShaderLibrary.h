#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "Shader.h"

typedef std::string ShaderID;

#define SHADER_RESOURCE_PATH "./shaders/"
#define VERTEXSHADERSRCFILENAME "vertex.glsl"
#define FRAGMENTSHADERSRCFILENAME "fragment.glsl"

class CShaderLibrary
{
public:
	CShaderLibrary() {};
	~CShaderLibrary() = default;

	void Init();
	static CShaderLibrary* Get();
	CShader& GetShader(const ShaderID& shaderID);

private:
	static CShaderLibrary* s_pCInstance;
	std::unordered_map<ShaderID, CShader> m_LibraryMap;
};