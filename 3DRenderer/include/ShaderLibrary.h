#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "Shader.h"

typedef std::string ShaderID;

#define SHADER_RESOURCE_PATH "./shaders/"
#define VERTEXSHADERSRCFILENAME "vertex.glsl"
#define FRAGMENTSHADERSRCFILENAME "fragment.glsl"

class ShaderLibrary
{
public:
	ShaderLibrary() {};
	~ShaderLibrary() = default;

	void Init();
	static ShaderLibrary* Get();
	Shader& GetShader(const ShaderID& shaderID);

private:
	static ShaderLibrary* s_Instance;
	std::unordered_map<ShaderID, Shader> m_Library;
};