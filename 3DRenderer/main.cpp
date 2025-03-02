#include <iostream>
#include <glm/glm.hpp>

#include "Application.h"

int main()
{
	Application* app = Application::Create({ 
		.WindowWidth = 800, 
		.WindowHeight = 600, 
		.BackgroundColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f),
		.ApplicationName = "Void Renderer", 
	});

	if (!app->Init())
	{
		std::cerr << "Could not initialize application" << std::endl;
		return -1;
	}

	app->Run();
	return 0;
}