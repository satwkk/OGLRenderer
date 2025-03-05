#include <iostream>
#include "Logger.h"

#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stbi_image.h"

Texture::Texture(const std::string& filePath, uint32_t slot) :
    m_TextureID(0),
    m_Slot(slot)
{
    int width, height, channels;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
    if (data == nullptr)
    {
        std::cerr << "could not load texture\n";
        exit(-1);
    }

    // TODO(void): Refactor this when material systems is in place
    glActiveTexture(GL_TEXTURE0 + m_Slot);
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);

    int format = channels == 4 ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture()
{
}

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0 + m_Slot);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture::UnBind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
