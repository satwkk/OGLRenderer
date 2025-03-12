#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader() = default;
	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~Shader();

	Shader(Shader& other) noexcept;
	Shader& operator=(Shader& other) noexcept;
	Shader(Shader&& other) noexcept;
	Shader& operator=(Shader&& other) noexcept;

	void Bind();
	void UnBind();

	const unsigned int GetRendererID() const { return m_RendererID; }
	void SetUniformMatrix4(const std::string& name, const glm::mat4& value);
	void SetUniformVector3(const std::string& name, const glm::vec3& value);
	void SetUniformFloat(const std::string& name, float value);
	void SetUniformInt(const std::string& name, int value);

private:
	uint32_t LoadShader(const std::string& shaderPath, unsigned int shaderType);

private:
	unsigned int m_RendererID;
};