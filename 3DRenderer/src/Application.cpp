#include "Application.h"

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLFW/glfw3.h"
#include "Shader.h"
#include "Window.h"

void UpdateCamera(GLFWwindow* pSWindow, CPerspectiveCamera& cCamera)
{
    if (bShouldMoveLight) return;
    glm::vec3 targetDir = glm::vec3(0.0f, 0.0f, 0.0f);
    float angle = 0.0f;

    if (glfwGetKey(pSWindow, GLFW_KEY_A))
    {
        targetDir = glm::vec3(-1.0f, 0.0f, 0.0f);
    }

    else if (glfwGetKey(pSWindow, GLFW_KEY_D))
    {
        targetDir = glm::vec3(1.0f, 0.0f, 0.0f);
    }

    else if (glfwGetKey(pSWindow, GLFW_KEY_W))
    {
        targetDir = glm::vec3(0.0f, 0.0f, -1.0f);
    }

    else if (glfwGetKey(pSWindow, GLFW_KEY_S))
    {
        targetDir = glm::vec3(0.0f, 0.0f, 1.0f);
    }

    double cursorPosX = 0.0;
    double cursorPosY = 0.0;
    glfwGetCursorPos(pSWindow, &cursorPosX, &cursorPosY);

    float deltaX = ((float)cursorPosX - fCursorPosLastFrameX) * fLightMoveSens; 
    float deltaY = ((float)cursorPosY - fCursorPosLastFrameY) * fLightMoveSens;

    cCamera.Rotate(deltaY, deltaX);
    cCamera.Move(targetDir);

    fCursorPosLastFrameX = (float)cursorPosX;
    fCursorPosLastFrameY = (float)cursorPosY;
}

void UpdateLight(GLFWwindow* pSWindow, CDirectionalLight& light)
{
    if (glfwGetKey(pSWindow, GLFW_KEY_Q))
    {
        glfwSetInputMode(pSWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        bShouldMoveLight = true;

    }
    else
    {
        glfwSetInputMode(pSWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        bShouldMoveLight = false;
    }

    if (!bShouldMoveLight) return;

    double mouseX, mouseY;
    glfwGetCursorPos(pSWindow, &mouseX, &mouseY);

    float deltaX = ((float)mouseX - fCursorPosLastFrameX) * fLightMoveSens; 
    float deltaY = ((float)mouseY - fCursorPosLastFrameY) * fLightMoveSens;

    if (glm::abs(deltaX) > 0.0001f || glm::abs(deltaY) > 0.0001f)
        light.SetRotation(glm::vec3(deltaY, deltaX, 0.0f));

    fCursorPosLastFrameX = (float)mouseX;
    fCursorPosLastFrameY = (float)mouseY;
}

CApplication* CApplication::s_pCInstance = nullptr;

CApplication::CApplication(const AppConfig& sConfig) :
    m_sConfig{ sConfig },
    m_CCamera{ glm::vec3{ 0.0f, 0.0f, 0.0f }, 1.f, 5000.f, m_sConfig.WindowWidth, m_sConfig.WindowHeight, 45.0f }
{
}

CApplication::~CApplication()
{
    m_CScene.CloseScene();
    glfwTerminate();
}

CApplication* CApplication::Create(const AppConfig& sConfig)
{
	return s_pCInstance = (s_pCInstance == nullptr) ? new CApplication(sConfig) : s_pCInstance;
}

bool CApplication::Init()
{
    m_pCMainWindow = std::make_unique<CWindow>(m_sConfig.WindowWidth, m_sConfig.WindowHeight, m_sConfig.ApplicationName);
    m_pCMainWindow->AddUpdateCallback([&]() { OnUpdate(); });
    m_pCMainWindow->EnableFlag(GL_CULL_FACE);
    m_pCMainWindow->EnableFlag(GL_DEPTH_TEST);

    m_CShaderLibrary.Init();

    // TODO(void): Load this based on setting file
    m_CShader = m_CShaderLibrary.GetShader("phong");

    // Add skybox
    // TODO(void): Move this to scene later
    m_pCSkybox = std::make_unique<CSkybox>();
    m_CSkyboxShader = m_CShaderLibrary.GetShader("cubemap");

    // TODO(void): Get it from shader library
    m_CShadowMappingShader = m_CShaderLibrary.GetShader("shadowmap");
    
    m_CDirectionalLight.Init(glm::vec3(0.0), glm::vec3(0.0, 0.0, -1.0));

    m_CScene.InitScene();

    return true;
}

void CApplication::Run()
{
    m_pCMainWindow->OnUpdate(0.f);
}

void CApplication::OnUpdate()
{
    vlog << "Light direction: " << m_CDirectionalLight.GetDirection().x << ", " << m_CDirectionalLight.GetDirection().y << ", " << m_CDirectionalLight.GetDirection().z << nl;

    // TODO(void): Implement a proper render pass system, light should not do the shadow pass
    m_CDirectionalLight.OnDraw(m_CShadowMappingShader, m_CScene);

    fCameraRotSinValueDebug += 0.1f;
    if (fCameraRotSinValueDebug > 360.0f) fCameraRotSinValueDebug -= 360.0f;

    m_CDirectionalLight.SetRotation(glm::vec3(0.0f, fCameraRotSinValueDebug, 0.0f));
    // UpdateLight(m_pCMainWindow->GetHandle(), m_CDirectionalLight);
    UpdateCamera(m_pCMainWindow->GetHandle(), m_CCamera);

    glViewport(0, 0, m_pCMainWindow->GetWidth(), m_pCMainWindow->GetHeight());

    // Render skybox
    m_pCSkybox->OnRender(m_CSkyboxShader, m_CCamera);

    m_CShader.Bind();

    // Camera View projection matrix
    m_CCamera.OnUpdate(m_CShader);

    // Position properties
    m_CShader.SetUniformVector3("light.direction", m_CDirectionalLight.GetDirection());
    m_CShader.SetUniformVector3("uCameraPosition", m_CCamera.GetPosition());
    m_CShader.SetUniformMatrix4("uLightSpaceMatrix", m_CDirectionalLight.GetViewProjectionMatrix());

    // Light properties
    m_CShader.SetUniformVector3("light.ambient", glm::vec3(0.2f));
    m_CShader.SetUniformVector3("light.diffuse", glm::vec3(0.5f));
    m_CShader.SetUniformVector3("light.specular", glm::vec3(1.0f));

    // Update scene
    m_CScene.OnUpdate(m_CShader);
}
