#pragma once

#include <GL/glew.h>

#include "DirectionalLight.h"
#include "Utility.h"
#include "Shader.h"
#include "Scene.h"

#define INVALID_RESOURCE_STATUS 0 

struct shadow_pass_framebuffer
{
    uint32_t FrameBufferID{ INVALID_RESOURCE_STATUS };
    uint32_t ShadowMapID{ INVALID_RESOURCE_STATUS };
    uint32_t ShadowMapWidth{ 0 };
    uint32_t ShadowMapHeight{ 0 };
};

static shadow_pass_framebuffer
CreateShadowPassFrameBuffer(uint32_t Width, uint32_t Height)
{
    shadow_pass_framebuffer Framebuffer;
    Framebuffer.ShadowMapWidth = Width;
    Framebuffer.ShadowMapHeight = Height;

    glGenFramebuffers(1, &Framebuffer.FrameBufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, Framebuffer.FrameBufferID);

    glGenTextures(1, &Framebuffer.ShadowMapID);
    glBindTexture(GL_TEXTURE_2D, Framebuffer.ShadowMapID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, Width, Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, Framebuffer.ShadowMapID, 0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    
    uint32_t status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        verr << "Frame buffer creation failed\n";
        Framebuffer = {};
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return(Framebuffer);
}

static void
BindFramebufferResource(shadow_pass_framebuffer* Framebuffer)
{
    glBindFramebuffer(GL_FRAMEBUFFER, Framebuffer->FrameBufferID);
}

static void
UnbindFramebufferResource()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

static void 
RunShadowPass(shadow_pass_framebuffer* pFrameBuffer, CDirectionalLight *Light, CShader& Shader, CScene& Scene, int WindowWidth, int WindowHeight)
{
    glViewport(0, 0, pFrameBuffer->ShadowMapWidth, pFrameBuffer->ShadowMapHeight);
    BindFramebufferResource(pFrameBuffer);
    glClear(GL_DEPTH_BUFFER_BIT);
    Shader.Bind();
    Shader.SetUniformMatrix4("uVPMatrix", Light->GetViewProjectionMatrix());
    glCullFace(GL_FRONT);
    Scene.OnUpdate(Shader);
    glCullFace(GL_BACK);
    Shader.UnBind();
    UnbindFramebufferResource();
    glViewport(0, 0, WindowWidth, WindowHeight);
}
