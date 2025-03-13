#pragma once

#include <vector>

#include "Texture.h"

class CCubeMap
{
public:
    CCubeMap() = default;
    ~CCubeMap() = default;

    void InitCubeMap(const std::vector<std::string>& texturePaths);
    void Release();
    void Bind();
    void UnBind();

private:
    uint32_t m_uTextureID;
};
