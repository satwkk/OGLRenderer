#pragma once

#include <vector>
#include <memory>
#include <string>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Window.h"
#include "Scene.h"
#include "ShaderLibrary.h"
#include "Texture.h"
#include "Skybox.h"

struct GLFWwindow;
class Model;
class Window;
class Camera;
class Shader;
class VertexBuffer;
class VertexArray;
class IndexBuffer;
class Texture;

struct AppConfig
{
	float WindowWidth;
	float WindowHeight;
	glm::vec4 BackgroundColor;
	std::string ApplicationName;
};

class Application
{
public:
	static Application* Create(const AppConfig& config);
	inline static Application* Get() { return s_Instance; }

	bool Init();
	void OnUpdate();
	void Run();

	inline Shader& GetShader() { return m_Shader; }
	inline Camera& GetSceneCamera() { return m_Camera; }

private:
	Application() = default;
	Application(const AppConfig& config);
	~Application();
	Application(const Application&) = delete;
	Application(Application&&) = delete;

private:
	static Application* s_Instance;

	AppConfig m_Config;
	std::unique_ptr<Window> m_pMainWindow;
	std::unique_ptr<Skybox> m_pSkybox;
	Camera m_Camera;
	Scene m_Scene;
	Shader m_SkyboxShader;
	ShaderLibrary m_ShaderLibrary;
	Shader m_Shader;
};


// =======================================================================================================
// TODO(void): Refactor this system into separate Input and GlobalLight system
// =======================================================================================================
static double cursorPosLastFrameX = 0.0;
static double cursorPosLastFrameY = 0.0;
static bool shouldMoveLight = false;
static double lightMoveSens = 2.f;
static glm::vec3 lightPosition(5.f, 10.0, 0.0f);
static glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

void UpdateCamera(GLFWwindow* window, Camera& camera);
void UpdateLight(GLFWwindow* window);