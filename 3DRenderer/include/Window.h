#pragma once
#include <string>
#include <functional>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct GLFWwindow;

class CWindow
{
public:
	CWindow() = default;
	CWindow(float width, float height, const std::string& name);
	~CWindow();

	void OnUpdate(float ts);
	void AddUpdateCallback(const std::function<void()>& updateCallback);
	void EnableFlag(uint32_t flag);
	void DisableFlag(uint32_t flag);
	bool bShouldClose();
	bool IsFlagEnabled(uint32_t flagBit);
	
	GLFWwindow* GetHandle() const { return m_pSHandle; }
	void SetBackgroundColor(const glm::vec3& color) { m_VWindowBackgroundColor = color; }
	const glm::vec3& GetBackgroundColor() const { return m_VWindowBackgroundColor; }

public:
	std::function<void()> m_fnUpdateCallback;

private:
	glm::vec3 m_VWindowBackgroundColor;
	uint32_t m_uEnabledFlags;
	GLFWwindow* m_pSHandle;
};