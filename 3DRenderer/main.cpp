#include <iostream>
#include <initializer_list>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#define STB_IMAGE_IMPLEMENTATION
#include "stbi_image.h"

#include "Utility.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "ModelLoader.h"
#include "Shader.h"
#include "Camera.h"

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

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Glfw failed\n";
        return -1;
    }

    auto* window = glfwCreateWindow(800, 600, "3D renderer", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        unsigned int errCode = glGetError();
        const GLubyte* errStr = glewGetErrorString(errCode);
        printf("GLEW ERROR: %s\n", errStr);
        glfwTerminate();
        return -1;
    }

    std::shared_ptr<Model> loadedModel = ModelLoader::Load("./res/models/Green_Sea_Turtle.fbx", BASICFLAGS);

    auto vertexArray = std::make_shared<VertexArray>();
    auto vertexBuffer = std::make_shared<VertexBuffer>(loadedModel->VertexData);
    auto indexBuffer = std::make_shared<IndexBuffer>(loadedModel->IndexData);

    vertexArray->AddBuffer(vertexBuffer);
    vertexArray->AddBuffer(indexBuffer);
    vertexArray->SetupLayouts();

    int width, height, channels;
    unsigned char* data = stbi_load("./res/models/container.jpg", &width, &height, &channels, 0);
    if (data == nullptr)
    {
        std::cerr << "could not load texture\n";
        return -1;
    }
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    int format = channels == 4 ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    std::unique_ptr<Shader> shader = std::make_unique<Shader>("./shaders/vertex.glsl", "./shaders/fragment.glsl");

    // Transformation matrix
    Camera camera(
        glm::vec3(0.0f, 0.0f, 0.0f),
        0.1f,
        1000.f,
        800.0f, 600.0f,
        45.0f
    );

    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        UpdateLight(window);
        UpdateCamera(window, camera);

        auto model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-90.f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

        shader->Use();

        // Set PHONG variables
        shader->SetUniformVector3("uLightPos", lightPosition);
        shader->SetUniformVector3("uLightColor", lightColor);
        shader->SetUniformVector3("uCameraPosition", camera.GetPosition());

        // Set MVP variables
        shader->SetUniformMatrix4("uVPMatrix", camera.GetVPMatrix());
        shader->SetUniformMatrix4("uModelMatrix", model);

        vertexArray->Bind();
        glDrawElements(GL_TRIANGLES, loadedModel->IndexData.size(), GL_UNSIGNED_INT, (void*)0);
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
	return 0;
}