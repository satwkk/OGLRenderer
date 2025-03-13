#pragma once

#include <vector>

#include "Texture.h"

class CubeMap
{
public:
    CubeMap() = default;
    ~CubeMap() = default;

    void InitCubeMap(const std::vector<std::string>& texturePaths);
    void Release();
    void Bind();
    void UnBind();

private:
    uint32_t m_TextureID;
};
