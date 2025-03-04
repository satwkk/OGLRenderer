#pragma once

#include "Camera.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <memory>
#include <string>

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
	void Run();

	inline std::shared_ptr<Shader>& GetShader() { return m_Shader; }
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
	std::shared_ptr<Window> m_MainWindow;

	Camera m_Camera;
	std::shared_ptr<Model> m_Model;
	std::shared_ptr<Shader> m_Shader;
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