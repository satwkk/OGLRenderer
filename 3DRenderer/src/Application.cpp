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

void UpdateCamera(GLFWwindow* window, Camera& camera)
{
    if (shouldMoveLight) return;
    glm::vec3 targetDir = glm::vec3(0.0f, 0.0f, 0.0f);
    float angle = 0.0f;

    if (glfwGetKey(window, GLFW_KEY_A))
    {
        targetDir = glm::vec3(-1.0f, 0.0f, 0.0f);
    }

    else if (glfwGetKey(window, GLFW_KEY_D))
    {
        targetDir = glm::vec3(1.0f, 0.0f, 0.0f);
    }

    else if (glfwGetKey(window, GLFW_KEY_W))
    {
        targetDir = glm::vec3(0.0f, 0.0f, -1.0f);
    }

    else if (glfwGetKey(window, GLFW_KEY_S))
    {
        targetDir = glm::vec3(0.0f, 0.0f, 1.0f);
    }

    double cursorPosX = 0.0;
    double cursorPosY = 0.0;
    glfwGetCursorPos(window, &cursorPosX, &cursorPosY);

    double deltaX = cursorPosX - cursorPosLastFrameX;
    double deltaY = cursorPosY - cursorPosLastFrameY;

    camera.Rotate(-deltaY, -deltaX);
    camera.Move(targetDir);

    cursorPosLastFrameX = cursorPosX;
    cursorPosLastFrameY = cursorPosY;
}

void UpdateLight(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_L))
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        shouldMoveLight = true;

    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        shouldMoveLight = false;
    }

    if (!shouldMoveLight) return;

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    float deltaX = mouseX - cursorPosLastFrameX;
    float deltaY = mouseY - cursorPosLastFrameY;

    lightPosition += glm::vec3(deltaX * lightMoveSens, 0.f, deltaY * lightMoveSens);

    cursorPosLastFrameX = mouseX;
    cursorPosLastFrameY = mouseY;
}

Application* Application::s_Instance = nullptr;

Application::Application(const AppConfig& config) :
    m_Config{ config },
    m_Camera{ glm::vec3{ 0.0f, 0.0f, 0.0f }, 1.f, 5000.f, m_Config.WindowWidth, m_Config.WindowHeight, 45.0f }
{
}

Application::~Application()
{
    m_Scene.CloseScene();
    glfwTerminate();
}

Application* Application::Create(const AppConfig& config)
{
	return s_Instance = (s_Instance == nullptr) ? new Application(config) : s_Instance;
}

bool Application::Init()
{
    // Create the window
    m_pMainWindow = std::make_unique<Window>(m_Config.WindowWidth, m_Config.WindowHeight, m_Config.ApplicationName);

    // Add on update callback
    m_pMainWindow->AddUpdateCallback([&]() { OnUpdate(); });

    // Enable depth testing
    m_pMainWindow->Enable(GL_DEPTH_TEST);

    // Initialize shader library
    m_ShaderLibrary.Init();

    // Get the phong shader model
    // TODO(void): Load this based on setting file
    m_Shader = m_ShaderLibrary.GetShader("phong");

    // Add skybox
    // TODO(void): Move this to scene later
    m_pSkybox = std::make_unique<Skybox>();
    m_SkyboxShader = m_ShaderLibrary.GetShader("cubemap");

    m_Scene.InitScene();

    return true;
}

void Application::Run()
{
    m_pMainWindow->OnUpdate(0.f);
}

void Application::OnUpdate()
{
    UpdateLight(m_pMainWindow->GetHandle());
    UpdateCamera(m_pMainWindow->GetHandle(), m_Camera);

    m_pSkybox->OnRender(m_SkyboxShader, m_Camera);

    m_Shader.Bind();

    // Camera View projection matrix
    m_Shader.SetUniformMatrix4("uVPMatrix", m_Camera.GetVPMatrix());

    // Position properties
    m_Shader.SetUniformVector3("light.position", lightPosition);
    m_Shader.SetUniformVector3("uCameraPosition", m_Camera.GetPosition());

    // Light properties
    m_Shader.SetUniformVector3("light.ambient", glm::vec3(0.2f));
    m_Shader.SetUniformVector3("light.diffuse", glm::vec3(0.5f));
    m_Shader.SetUniformVector3("light.specular", glm::vec3(1.0f));

    // Update scene
    m_Scene.OnUpdate(m_Shader);
}
