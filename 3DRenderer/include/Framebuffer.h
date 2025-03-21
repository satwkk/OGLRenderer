#pragma once

#include <stdint.h>
#include "Shader.h"

struct FramebufferSpecification
{
    uint32_t uWidth{ 0 }, uHeight{ 0 };
    bool bDisableColorBuffer{ false };
};

class CFramebuffer
{
public:
    CFramebuffer() = default;
    CFramebuffer(FramebufferSpecification&& spec);
    ~CFramebuffer();

    void Bind();
    void Unbind();

    inline int GetWidth() { return m_SFrameBufferSpecification.uWidth; }
    inline int GetHeight() { return m_SFrameBufferSpecification.uHeight; }
    inline uint32_t GetTexture() { return m_uTextureID; }

private:
    FramebufferSpecification m_SFrameBufferSpecification{};
    uint32_t m_uFrameBufferID{0};
    uint32_t m_uTextureID{0};
};
