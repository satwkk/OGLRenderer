#include "Framebuffer.h"

#include <GL/glew.h>

CFramebuffer::CFramebuffer(FramebufferSpecification&& spec) :
    m_SFrameBufferSpecification(std::move(spec))
{
    // Create frame buffer
    glGenFramebuffers(1, &m_uFrameBufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, m_uFrameBufferID);

    // Create texture
    glGenTextures(1, &m_uTextureID);
    glBindTexture(GL_TEXTURE_2D, m_uTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, spec.uWidth, spec.uHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Assign texture to framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_uTextureID, 0);

    if (spec.bDisableColorBuffer)
    {
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

CFramebuffer::~CFramebuffer()
{
}

void CFramebuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_uFrameBufferID);
}

void CFramebuffer::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
