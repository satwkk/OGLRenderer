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
class CModel;
class CWindow;
class CPerspectiveCamera;
class CShader;
class VertexBuffer;
class CVertexArray;
class IndexBuffer;
class CTexture;

struct AppConfig
{
	float WindowWidth;
	float WindowHeight;
	glm::vec4 BackgroundColor;
	std::string ApplicationName;
};

class CApplication
{
public:
	static CApplication* Create(const AppConfig& sConfig);
	inline static CApplication* Get() { return s_pCInstance; }

	bool Init();
	void OnUpdate();
	void Run();

	inline CShader& GetShader() { return m_cShader; }
	inline CPerspectiveCamera& GetSceneCamera() { return m_cCamera; }

private:
	CApplication() = default;
	CApplication(const AppConfig& config);
	~CApplication();
	CApplication(const CApplication&) = delete;
	CApplication(CApplication&&) = delete;

private:
	static CApplication* s_pCInstance;

	AppConfig m_sConfig;
	std::unique_ptr<CWindow> m_pCMainWindow;
	std::unique_ptr<CSkybox> m_pCSkybox;
	CPerspectiveCamera m_cCamera;
	CScene m_cScene;
	CShader m_cSkyboxShader;
	CShaderLibrary m_cShaderLibrary;
	CShader m_cShader;
};


// =======================================================================================================
// TODO(void): Refactor this system into separate Input and GlobalLight system
// =======================================================================================================
static double dCursorPosLastFrameX = 0.0;
static double dCursorPosLastFrameY = 0.0;
static bool bShouldMoveLight = false;
static double dLightMoveSens = 2.f;
static glm::vec3 vLightPosition(5.f, 10.0, 0.0f);
static glm::vec3 vLightColor = glm::vec3(1.0f, 1.0f, 1.0f);

void UpdateCamera(GLFWwindow* pWindow, CPerspectiveCamera& cCamera);
void UpdateLight(GLFWwindow* pWindow);