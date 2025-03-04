#include "Shader.h"
#include "Utility.h"

#include <GL/glew.h>

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    : m_RendererID(0)
{
    uint32_t vs = LoadShader(vertexShaderPath, GL_VERTEX_SHADER);
    uint32_t fs = LoadShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

    assert(vs != -1);
    assert(fs != -1);

    m_RendererID = glCreateProgram();
    glAttachShader(m_RendererID, vs);
    glAttachShader(m_RendererID, fs);
    glLinkProgram(m_RendererID);

    // Link program
    {
        int param;
        glGetProgramiv(m_RendererID, GL_LINK_STATUS, &param);
        if (!param)
        {
            char buffer[1024];
            glGetProgramInfoLog(m_RendererID, 1024, nullptr, buffer);
            printf("Fragment shader compilation error: %s\n", buffer);
            return;
        }
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
    glUseProgram(0);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

void Shader::Bind()
{
    glUseProgram(m_RendererID);
}

void Shader::UnBind()
{
    glUseProgram(0);
}

void Shader::SetUniformMatrix4(const std::string& name, const glm::mat4& value)
{
    auto location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetUniformVector3(const std::string& name, const glm::vec3& value)
{
    auto location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform3fv(location, 1, glm::value_ptr(value));
}

void Shader::SetUniformFloat(const std::string& name, float value)
{
    auto location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform1f(location, value);
}

void Shader::SetUniformInt(const std::string& name, int value)
{
    auto location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform1i(location, value);
}

uint32_t Shader::LoadShader(const std::string& shaderPath, unsigned int shaderType)
{
    std::string shaderString = Utility::ReadFile(shaderPath);
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
