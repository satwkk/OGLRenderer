#include <GL/glew.h>
#include <glm/glm.hpp>
#include "CubeMap.h"
#include "Logger.h"
#include "stbi_image.h"

void CCubeMap::InitCubeMap(const std::vector<std::string>& texturePaths)
{
    glGenTextures(1, &m_uTextureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_uTextureID);
    
    int nWidth, nHeight, nChannels = 0;
    for (uint32_t i = 0; i < texturePaths.size(); i++)
    {
        void* pData = stbi_load(texturePaths[i].c_str(), &nWidth, &nHeight, &nChannels, 0);
        if (!pData)
        {
            verr << "Could not load cubmap textures\n";
            return;
        }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, nWidth, nHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pData);
        stbi_image_free(pData);
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CCubeMap::Release()
{
    glDeleteTextures(1, &m_uTextureID);
}

void CCubeMap::Bind()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_uTextureID);
}

void CCubeMap::UnBind()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
