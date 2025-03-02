#include <iostream>
#include <GLFW/glfw3.h>

#include "Window.h"

Window::Window(float width, float height, const std::string& name) :
	m_Handle(nullptr)
{
	m_Handle = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

	if (m_Handle == nullptr)
	{
		std::cerr << "Could not create GLFW window" << std::endl;
		return;
	}

	std::cout << "Window Created: " << name << std::endl;
}

Window::~Window()
{
	glfwDestroyWindow(m_Handle);
}
