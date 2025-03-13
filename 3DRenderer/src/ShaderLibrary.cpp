#include <filesystem>

#include "ShaderLibrary.h"
#include "Utility.h"

ShaderLibrary* ShaderLibrary::s_Instance = nullptr;

void ShaderLibrary::Init()
{
	std::filesystem::path shaderPath{ SHADER_RESOURCE_PATH };
	for (auto& entry : std::filesystem::directory_iterator(shaderPath))
	{
		if (entry.is_directory())
		{
			std::string dirAbsPath{ entry.path().string() };
			std::string dirName{ dirAbsPath.substr(dirAbsPath.find_last_of('/') + 1, dirAbsPath.size()) };

			// TODO(void): Maybe search for the files instead of hardcoding like this ??
			std::string vertexFile = dirAbsPath + "/" + VERTEXSHADERSRCFILENAME;
			std::string fragmentFile = dirAbsPath + "/" + FRAGMENTSHADERSRCFILENAME;

			if (std::filesystem::exists({ vertexFile }) && std::filesystem::exists({ fragmentFile }))
			{
				vlog << "Adding shaders for: " << dirName << nl;
				m_Library.emplace(dirName, Shader{ vertexFile, fragmentFile });
			}
		}
	}
}

ShaderLibrary* ShaderLibrary::Get()
{
	if (s_Instance == nullptr)
	{
		s_Instance = new ShaderLibrary;
	}
	return s_Instance;
}

Shader& ShaderLibrary::GetShader(const ShaderID& id)
{
	const auto it = m_Library.find(id);
	ASSERT(it != m_Library.end());
	return it->second;
}
