#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Application.h"
#include "Window.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stbi_image.h"

#include "Utility.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "ModelLoader.h"
#include "Shader.h"

// =======================================================================================================
// TODO(void): Refactor this system into separate Input and GlobalLight system
// =======================================================================================================
double cursorPosLastFrameX = 0.0;
double cursorPosLastFrameY = 0.0;
bool shouldMoveLight = false;
double lightMoveSens = 2.f;
glm::vec3 lightPosition(150.0f, 50.0f, 0.0f);
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

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

    lightPosition += glm::vec3(deltaX * lightMoveSens, deltaY * lightMoveSens, 0.0f);

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
        std::cerr << "Glfw failed\n";
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
        printf("GLEW ERROR: %s\n", errStr);
        glfwTerminate();
        return false;
    }

    m_Model = ModelLoader::Load("./res/models/Green_Sea_Turtle.fbx", BASICFLAGS);

    m_VertexArray = std::make_shared<VertexArray>();
    m_VertexBuffer = std::make_shared<VertexBuffer>(m_Model->VertexData);
    m_IndexBuffer = std::make_shared<IndexBuffer>(m_Model->IndexData);

    m_VertexArray->AddBuffer(m_VertexBuffer);
    m_VertexArray->AddBuffer(m_IndexBuffer);
    m_VertexArray->SetupLayouts();

    int width, height, channels;
    unsigned char* data = stbi_load("./res/models/container.jpg", &width, &height, &channels, 0);
    if (data == nullptr)
    {
        std::cerr << "could not load texture\n";
        return false;
    }

    // TODO(void): Refactor this when material systems is in place
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    int format = channels == 4 ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    m_Shader = std::make_shared<Shader>("./shaders/vertex.glsl", "./shaders/fragment.glsl");

    // Enable depth testing
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    return true;
}

void Application::Run()
{
    while (!glfwWindowShouldClose(m_MainWindow->GetHandle()))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(m_Config.BackgroundColor.x, m_Config.BackgroundColor.y, m_Config.BackgroundColor.z, m_Config.BackgroundColor.w);

        UpdateLight(m_MainWindow->GetHandle());
        UpdateCamera(m_MainWindow->GetHandle(), m_Camera);

        auto model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-90.f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

        m_Shader->Use();

        // Set PHONG variables
        m_Shader->SetUniformVector3("uLightPos", lightPosition);
        m_Shader->SetUniformVector3("uLightColor", lightColor);
        m_Shader->SetUniformVector3("uCameraPosition", m_Camera.GetPosition());

        // Set MVP variables
        m_Shader->SetUniformMatrix4("uVPMatrix", m_Camera.GetVPMatrix());
        m_Shader->SetUniformMatrix4("uModelMatrix", model);

        m_VertexArray->Bind();
        glDrawElements(GL_TRIANGLES, m_Model->IndexData.size(), GL_UNSIGNED_INT, (void*)0);
        glfwSwapBuffers(m_MainWindow->GetHandle());
    }
}
