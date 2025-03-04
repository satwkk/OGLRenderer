#include "Renderer.h"
#include "Logger.h"
#include "Shader.h"
#include "VertexArray.h"

Renderer* Renderer::s_Instance = nullptr;

bool Renderer::Init()
{
	if (s_Instance == nullptr)
	{
		s_Instance = new Renderer();
		return true;
	}

	verr << "Trying to instantiate another renderer. Aborting...\n";
	return false;
}

void Renderer::ShutDown()
{
	delete s_Instance;
}

void Renderer::Render(std::shared_ptr<Shader>& shader, std::shared_ptr<VertexArray>& vertexArray)
{
}
