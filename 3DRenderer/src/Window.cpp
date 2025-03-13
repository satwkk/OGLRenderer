#include <iostream>

#include "Window.h"
#include "Logger.h"

Window::Window(float width, float height, const std::string& name) :
	m_Handle { nullptr },
	m_WindowBackgroundColor{ 0.1f, 0.1f, 0.1f },
	m_EnabledFlags{ 0 }
{
	// Init GLFW
	if (!glfwInit())
	{
		verr << "GLFW Failed to initialize\n";
		return;
	}

	m_Handle = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

	if (m_Handle == nullptr)
	{
		std::cerr << "Could not create GLFW window" << std::endl;
		return;
	}

	std::cout << "Window Created: " << name << std::endl;

	// Setup context
	glfwMakeContextCurrent(m_Handle);

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

Window::~Window()
{
	glfwDestroyWindow(m_Handle);
}

void Window::OnUpdate(float ts)
{
	glDepthRange(0.0f, 1.0f);
	glClearDepth(1.0f);
	while (!bShouldClose())
	{
		glfwPollEvents();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glClearColor(m_WindowBackgroundColor.r, m_WindowBackgroundColor.g, m_WindowBackgroundColor.b, 1.0f);
		m_UpdateCallback();
		glfwSwapBuffers(m_Handle);
	}
}

void Window::AddUpdateCallback(const std::function<void()>& updateCallback)
{
	m_UpdateCallback = updateCallback;
}

bool Window::bShouldClose()
{
	return glfwWindowShouldClose(m_Handle);
}

void Window::Enable(uint32_t enableFlag)
{
	glEnable(enableFlag);
	m_EnabledFlags |= enableFlag;
}
