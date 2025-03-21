#pragma once

#include <memory>
#include <string>
#include <glm/glm.hpp>

#include "PerspectiveCamera.h"
#include "Window.h"
#include "Scene.h"
#include "ShaderLibrary.h"
#include "Skybox.h"
#include "DirectionalLight.h"

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

	inline CShader& GetShader() { return m_CShader; }
	inline CPerspectiveCamera& GetSceneCamera() { return m_CCamera; }
	// TEMP: This shouldn't be here.
	inline CDirectionalLight& GetDirectionalLight() { return m_CDirectionalLight; }

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
	CPerspectiveCamera m_CCamera;
	CScene m_CScene;
	CShader m_CSkyboxShader;
	CShaderLibrary m_CShaderLibrary;
	CShader m_CShader;
	CShader m_CShadowMappingShader;
	CDirectionalLight m_CDirectionalLight;
    float fCameraRotSinValueDebug;
};


// =======================================================================================================
// TODO(void): Refactor this system into separate Input system
// =======================================================================================================
static float fCursorPosLastFrameX = 0.0;
static float fCursorPosLastFrameY = 0.0;
static bool bShouldMoveLight = false;
static float fLightMoveSens = 1.f;

void UpdateCamera(GLFWwindow* pWindow, CPerspectiveCamera& cCamera);
void UpdateLight(GLFWwindow* pWindow, CDirectionalLight& light);
