#include "Shader.h"
#include "Utility.h"

#include <GL/glew.h>

CShader::CShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    : m_uRendererID(0)
{
    uint32_t vs = LoadShader(vertexShaderPath, GL_VERTEX_SHADER);
    uint32_t fs = LoadShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

    assert(vs != -1);
    assert(fs != -1);

    m_uRendererID = glCreateProgram();
    glAttachShader(m_uRendererID, vs);
    glAttachShader(m_uRendererID, fs);
    glLinkProgram(m_uRendererID);

    // Link program
    {
        int param;
        glGetProgramiv(m_uRendererID, GL_LINK_STATUS, &param);
        if (!param)
        {
            char buffer[1024];
            glGetProgramInfoLog(m_uRendererID, 1024, nullptr, buffer);
            printf("Program link error: %s\n", buffer);
            return;
        }
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
}

CShader::~CShader()
{
    glDeleteProgram(m_uRendererID);
}

CShader::CShader(CShader& other) noexcept
{
    vlog << "Shader copy constructor called\n";
    m_uRendererID = other.m_uRendererID;
}

CShader& CShader::operator=(CShader& other) noexcept
{
    vlog << "Shader copy assignment called\n";
    m_uRendererID = other.m_uRendererID; 
    return *this;
}

CShader::CShader(CShader&& other) noexcept
{
    vlog << "Shader move constructor called\n";
    m_uRendererID = other.m_uRendererID;
    other.m_uRendererID = 0;
}

CShader& CShader::operator=(CShader&& other) noexcept
{
    vlog << "Shader move assignment called\n";
    m_uRendererID = other.m_uRendererID;
    other.m_uRendererID = 0;
    return *this;
}

void CShader::Bind()
{
    m_bIsInUse = true;
    glUseProgram(m_uRendererID);
}

void CShader::UnBind()
{
    m_bIsInUse = false;
    glUseProgram(0);
}

void CShader::SetUniformMatrix4(const std::string& name, const glm::mat4& value)
{
    auto location = glGetUniformLocation(m_uRendererID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void CShader::SetUniformVector3(const std::string& name, const glm::vec3& value)
{
    auto location = glGetUniformLocation(m_uRendererID, name.c_str());
	glUniform3fv(location, 1, glm::value_ptr(value));
}

void CShader::SetUniformFloat(const std::string& name, float value)
{
    auto location = glGetUniformLocation(m_uRendererID, name.c_str());
	glUniform1f(location, value);
}

void CShader::SetUniformInt(const std::string& name, int value)
{
    auto location = glGetUniformLocation(m_uRendererID, name.c_str());
	glUniform1i(location, value);
}

uint32_t CShader::LoadShader(const std::string& shaderPath, unsigned int shaderType)
{
    std::string shaderString = CUtility::ReadFile(shaderPath);
    const char* shaderSrc = shaderString.c_str();

    unsigned int shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, 1, &shaderSrc, nullptr);
    glCompileShader(shaderID);

    // Error checking
    {
        int param;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &param);
        if (!param)
        {
            char buffer[1024];
            glGetShaderInfoLog(shaderID, 1024, nullptr, buffer);
            printf("Vertex shader compilation error: %s\n", buffer);
            return -1;
        }
    }
    return shaderID;
}
