#include <GL/glew.h>
#include <glm/glm.hpp>
#include "CubeMap.h"
#include "Logger.h"
#include "stbi_image.h"

void CubeMap::InitCubeMap(const std::vector<std::string>& texturePaths)
{
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);
    
    int x, y, channels = 0;
    for (uint32_t i = 0; i < texturePaths.size(); i++)
    {
        void* data = stbi_load(texturePaths[i].c_str(), &x, &y, &channels, 0);
        if (!data)
        {
            verr << "Could not load cubmap textures\n";
            return;
        }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeMap::Release()
{
    glDeleteTextures(1, &m_TextureID);
}

void CubeMap::Bind()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);
}

void CubeMap::UnBind()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
