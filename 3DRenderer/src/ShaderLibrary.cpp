#include <filesystem>

#include "ShaderLibrary.h"
#include "Utility.h"

CShaderLibrary* CShaderLibrary::s_pCInstance = nullptr;

void CShaderLibrary::Init()
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
				m_LibraryMap.emplace(dirName, CShader{ vertexFile, fragmentFile });
			}
		}
	}
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
