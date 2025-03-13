#pragma once
#include <string>
#include <functional>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct GLFWwindow;

class Window
{
public:
	Window() = default;
	Window(float width, float height, const std::string& name);
	~Window();

	void Enable(uint32_t enableFlag);
	void OnUpdate(float ts);
	void AddUpdateCallback(const std::function<void()>& updateCallback);
	bool bShouldClose();
	
	GLFWwindow* GetHandle() const { return m_Handle; }
	void SetBackgroundColor(const glm::vec3& color) { m_WindowBackgroundColor = color; }
	const glm::vec3& GetBackgroundColor() const { return m_WindowBackgroundColor; }

public:
	std::function<void()> m_UpdateCallback;

private:
	glm::vec3 m_WindowBackgroundColor;
	uint32_t m_EnabledFlags;
	GLFWwindow* m_Handle;
};