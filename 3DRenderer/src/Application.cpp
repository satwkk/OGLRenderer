#include "Application.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Utility.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "ModelLoader.h"
#include "Shader.h"
#include "SceneObject.h"
#include "Logger.h"

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

    double deltaX = cursorPosX - dCursorPosLastFrameX;
    double deltaY = cursorPosY - dCursorPosLastFrameY;

    cCamera.Rotate(-deltaY, -deltaX);
    cCamera.Move(targetDir);

    dCursorPosLastFrameX = cursorPosX;
    dCursorPosLastFrameY = cursorPosY;
}

void UpdateLight(GLFWwindow* pSWindow)
{
    if (glfwGetKey(pSWindow, GLFW_KEY_L))
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

    float deltaX = mouseX - dCursorPosLastFrameX;
    float deltaY = mouseY - dCursorPosLastFrameY;

    vLightPosition += glm::vec3(deltaX * dLightMoveSens, 0.f, deltaY * dLightMoveSens);

    dCursorPosLastFrameX = mouseX;
    dCursorPosLastFrameY = mouseY;
}

CApplication* CApplication::s_pCInstance = nullptr;

CApplication::CApplication(const AppConfig& sConfig) :
    m_sConfig{ sConfig },
    m_cCamera{ glm::vec3{ 0.0f, 0.0f, 0.0f }, 1.f, 5000.f, m_sConfig.WindowWidth, m_sConfig.WindowHeight, 45.0f }
{
}

CApplication::~CApplication()
{
    m_cScene.CloseScene();
    glfwTerminate();
}

CApplication* CApplication::Create(const AppConfig& sConfig)
{
	return s_pCInstance = (s_pCInstance == nullptr) ? new CApplication(sConfig) : s_pCInstance;
}

bool CApplication::Init()
{
    // Create the window
    m_pCMainWindow = std::make_unique<CWindow>(m_sConfig.WindowWidth, m_sConfig.WindowHeight, m_sConfig.ApplicationName);

    // Add on update callback
    m_pCMainWindow->AddUpdateCallback([&]() { OnUpdate(); });

    // Enable depth testing
    m_pCMainWindow->Enable(GL_DEPTH_TEST);

    // Initialize shader library
    m_cShaderLibrary.Init();

    // Get the phong shader model
    // TODO(void): Load this based on setting file
    m_cShader = m_cShaderLibrary.GetShader("phong");

    // Add skybox
    // TODO(void): Move this to scene later
    m_pCSkybox = std::make_unique<CSkybox>();
    m_cSkyboxShader = m_cShaderLibrary.GetShader("cubemap");

    m_cScene.InitScene();

    return true;
}

void CApplication::Run()
{
    m_pCMainWindow->OnUpdate(0.f);
}

void CApplication::OnUpdate()
{
    UpdateLight(m_pCMainWindow->GetHandle());
    UpdateCamera(m_pCMainWindow->GetHandle(), m_cCamera);

    m_pCSkybox->OnRender(m_cSkyboxShader, m_cCamera);

    m_cShader.Bind();

    // Camera View projection matrix
    m_cShader.SetUniformMatrix4("uVPMatrix", m_cCamera.GetVPMatrix());

    // Position properties
    m_cShader.SetUniformVector3("light.position", vLightPosition);
    m_cShader.SetUniformVector3("uCameraPosition", m_cCamera.GetPosition());

    // Light properties
    m_cShader.SetUniformVector3("light.ambient", glm::vec3(0.2f));
    m_cShader.SetUniformVector3("light.diffuse", glm::vec3(0.5f));
    m_cShader.SetUniformVector3("light.specular", glm::vec3(1.0f));

    // Update scene
    m_cScene.OnUpdate(m_cShader);
}
