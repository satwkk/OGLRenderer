#include <iostream>

#include "Window.h"
#include "Logger.h"

CWindow::CWindow(float width, float height, const std::string& name) :
	m_pSHandle { nullptr },
	m_fWidth{ width },
	m_fHeight{ height },
	m_VWindowBackgroundColor{ 0.1f, 0.1f, 0.1f },
	m_uEnabledFlags{ 0 }
{
	// Init GLFW
	if (!glfwInit())
	{
		verr << "GLFW Failed to initialize\n";
		return;
	}

	m_pSHandle = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

	if (m_pSHandle == nullptr)
	{
		std::cerr << "Could not create GLFW window" << std::endl;
		return;
	}

	std::cout << "Window Created: " << name << std::endl;

	// Setup context
	glfwMakeContextCurrent(m_pSHandle);

	// Init GLEW OpenGL loader
	if (glewInit() != GLEW_OK)
	{
		unsigned int errCode = glGetError();
		const GLubyte* errStr = glewGetErrorString(errCode);
		verr << "GLEW Failed to initialize\n";
		printf("%s\n", errStr);
		return;
	}
}

CWindow::~CWindow()
{
	glfwDestroyWindow(m_pSHandle);
}

void CWindow::OnUpdate(float ts)
{
	while (!bShouldClose())
	{
		glfwPollEvents();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glClearColor(m_VWindowBackgroundColor.r, m_VWindowBackgroundColor.g, m_VWindowBackgroundColor.b, 1.0f);
		m_fnUpdateCallback();
		glfwSwapBuffers(m_pSHandle);
	}
}

void CWindow::AddUpdateCallback(const std::function<void()>& updateCallback)
{
	m_fnUpdateCallback = updateCallback;
}

bool CWindow::bShouldClose()
{
	return glfwWindowShouldClose(m_pSHandle);
}

void CWindow::EnableFlag(uint32_t flag)
{
	glEnable(flag);
	m_uEnabledFlags |= flag;
}

void CWindow::DisableFlag(uint32_t flag)
{
	glDisable(flag);
	m_uEnabledFlags &= ~flag;
}

bool CWindow::IsFlagEnabled(uint32_t flagBit)
{
	return (m_uEnabledFlags & flagBit) == flagBit;
}
