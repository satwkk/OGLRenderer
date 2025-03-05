#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Application.h"
#include "Window.h"

#include "Utility.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "ModelLoader.h"
#include "Shader.h"
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
	m_Config(config),
    m_Camera(glm::vec3(0.0f, 0.0f, 0.0f), 0.1f, 1000.f, m_Config.WindowWidth, m_Config.WindowHeight, 45.0f)
{
}

Application::~Application()
{
    glfwTerminate();
}

Application* Application::Create(const AppConfig& config)
{
	return s_Instance = (s_Instance == nullptr) ? new Application(config) : s_Instance;
}

bool Application::Init()
{
    // Init GLFW
    if (!glfwInit())
    {
        verr << "GLFW Failed to initialize\n";
        return false;
    }

    // Create the window
    m_MainWindow = std::make_shared<Window>(m_Config.WindowWidth, m_Config.WindowHeight, m_Config.ApplicationName);

    // Setup context
    glfwMakeContextCurrent(m_MainWindow->GetHandle());

    // Init GLEW OpenGL loader
    if (glewInit() != GLEW_OK)
    {
        unsigned int errCode = glGetError();
        const GLubyte* errStr = glewGetErrorString(errCode);
        verr << "GLEW Failed to initialize\n";
        printf("%s\n", errStr);
        glfwTerminate();
        return false;
    }

    m_Shader = std::make_shared<Shader>("./shaders/vertex.glsl", "./shaders/fragment.glsl");

    m_Models = {
        ModelLoader::Load("./res/models/tree/Gledista_Triacanthos.fbx", BASICFLAGS),
        ModelLoader::Load("./res/models/tree/Gledista_Triacanthos_2.fbx", BASICFLAGS),
        ModelLoader::Load("./res/models/tree/Gledista_Triacanthos_3.fbx", BASICFLAGS),
        ModelLoader::Load("./res/models/tree/Gledista_Triacanthos_4.fbx", BASICFLAGS),
        ModelLoader::Load("./res/models/tree/Gledista_Triacanthos_5.fbx", BASICFLAGS),
        ModelLoader::Load("./res/models/tree/Gledista_Triacanthos_6.fbx", BASICFLAGS)
    };


    for (uint32_t i = 0; i < m_Models.size(); i++)
    {
        glm::vec3 pos = glm::vec3(0.0f);
        pos.x += rand() % 100;
        pos.z += rand() % 100;
        m_Models[i]->SetPosition(pos);
    }

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    return true;
}

void Application::Run()
{
    while (!glfwWindowShouldClose(m_MainWindow->GetHandle()))
    {
        glfwPollEvents();
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glClearColor(m_Config.BackgroundColor.x, m_Config.BackgroundColor.y, m_Config.BackgroundColor.z, m_Config.BackgroundColor.w);

        UpdateLight(m_MainWindow->GetHandle());
        UpdateCamera(m_MainWindow->GetHandle(), m_Camera);

        m_Shader->Bind();

        // Camera View projection matrix
        m_Shader->SetUniformMatrix4("uVPMatrix", m_Camera.GetVPMatrix());

        // Position properties
        m_Shader->SetUniformVector3("light.position", lightPosition);
        m_Shader->SetUniformVector3("uCameraPosition", m_Camera.GetPosition());

        // Light properties
        m_Shader->SetUniformVector3("light.ambient", glm::vec3(0.2f));
        m_Shader->SetUniformVector3("light.diffuse", glm::vec3(0.5f));
        m_Shader->SetUniformVector3("light.specular", glm::vec3(1.0f));

        // Bind texture
        for (auto& model : m_Models)
        {
            model->OnDraw(m_Shader);
        }

        glfwSwapBuffers(m_MainWindow->GetHandle());
    }
}
