#include <iostream>
#include "Logger.h"

#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <GL/glew.h>

#include "stbi_image.h"

CTexture::CTexture(const std::string& filePath, uint32_t slot) :
m_uTextureID{0},
m_uSlot{slot}
{
    int width, height, channels;
    
    unsigned char* pData = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
    if (pData == nullptr)
    {
        std::cerr << "could not load texture\n";
        exit(-1);
    }

    // TODO(void): Refactor this when material systems is in place
    glActiveTexture(GL_TEXTURE0 + m_uSlot);
    glGenTextures(1, &m_uTextureID);
    glBindTexture(GL_TEXTURE_2D, m_uTextureID);

    int format = channels == 4 ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pData);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glGenerateMipmap(GL_TEXTURE_2D);
}

CTexture::~CTexture()
{
}

void CTexture::Bind()
{
    glActiveTexture(GL_TEXTURE0 + m_uSlot);
    glBindTexture(GL_TEXTURE_2D, m_uTextureID);
}

void CTexture::UnBind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

