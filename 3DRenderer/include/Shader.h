#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class CShader
{
public:
	CShader() = default;
	CShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~CShader();

	CShader(CShader& other) noexcept;
	CShader& operator=(CShader& other) noexcept;
	CShader(CShader&& other) noexcept;
	CShader& operator=(CShader&& other) noexcept;

	void Bind();
	void UnBind();

	const unsigned int GetRendererID() const { return m_uRendererID; }
	void SetUniformMatrix4(const std::string& name, const glm::mat4& value);
	void SetUniformVector3(const std::string& name, const glm::vec3& value);
	void SetUniformFloat(const std::string& name, float value);
	void SetUniformInt(const std::string& name, int value);

	inline const bool IsBound() const { return m_bIsInUse; }

private:
	uint32_t LoadShader(const std::string& shaderPath, unsigned int shaderType);

private:
	unsigned int m_uRendererID;
	bool m_bIsInUse;
};