#include <iostream>
#include <glm/glm.hpp>

#include "Application.h"

int main()
{
	Application* app = Application::Create({ 
		.WindowWidth = 1024, 
		.WindowHeight = 768, 
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