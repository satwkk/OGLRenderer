#pragma once

#include <string>

struct GLFWwindow;

class Window
{
public:
	Window() = default;
	Window(float width, float height, const std::string& name);
	~Window();

	inline GLFWwindow* GetHandle() const { return m_Handle; }

private:
	GLFWwindow* m_Handle;
};